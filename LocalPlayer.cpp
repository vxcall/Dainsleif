#include "pch.h"
#include "LocalPlayer.h"
#include "offsets.h"
#include <iostream>
#include <Windows.h>
#include "vector3.h"
#include <math.h>
#include <cmath>


LocalPlayer* GetLocalPlayer(uintptr_t moduleBase)
{
	LocalPlayer* lp = reinterpret_cast<LocalPlayer*>((moduleBase + dwLocalPlayer)); //get local player address and cast it to my original class type
	return lp;
}

float LocalPlayer::GetDistance(Vector3 targetPos, Vector3& deltaVector)
{
    deltaVector =  targetPos - *this->GetHeadPosition(); //minus operation is defined in vector3.h
	float distance = sqrt(deltaVector.x * deltaVector.x + deltaVector.y * deltaVector.y + deltaVector.z * deltaVector.z); //This is the trigonometry calculation to get hypnotenuse.
	return distance;
}

float LocalPlayer::GetDistance(Vector3 targetPos)
{
	Vector3 deltaVector = targetPos - *this->GetBodyPosition();
	float distance = sqrt(deltaVector.x * deltaVector.x + deltaVector.y * deltaVector.y + deltaVector.z * deltaVector.z);
	return distance;
}

Vector3* LocalPlayer::GetBodyPosition()
{
	return reinterpret_cast<Vector3*>((*(uintptr_t*)this + m_vecOrigin));
}

Vector3* LocalPlayer::GetViewOffset()
{
	return reinterpret_cast<Vector3*>((*(uintptr_t*)this + m_vecViewOffset));
}

Vector3* LocalPlayer::GetHeadPosition()
{
	Vector3 bp = *(this->GetBodyPosition()); //get position and dereference it to calculate later on.
	Vector3 vo = *(this->GetViewOffset()); //get viewoffset and dereference it to calculate later on.
	Vector3* headPosition = &(bp + vo); //calculate them and store the result into pointer variable.
	return headPosition;
}

int* LocalPlayer::GetHealth()
{
	return reinterpret_cast<int*>((*(uintptr_t*)this + m_iHealth));
}

int* LocalPlayer::GetTeam()
{
	return reinterpret_cast<int*>((*(uintptr_t*)this + m_iTeamNum));
}

double PI = 3.14159265358;
void LocalPlayer::AimBot(Vector3 TargetsHeadPosition)
{
	static uintptr_t engineModule = reinterpret_cast<uintptr_t>(GetModuleHandle(L"engine.dll"));
	static Vector3* viewAngles = reinterpret_cast<Vector3*>((*reinterpret_cast<uintptr_t*>((engineModule + dwClientState)) + dwClientState_ViewAngles));
	Vector3 delta;
	float hypotenuse = GetDistance(TargetsHeadPosition, delta);
	float pitch = -asin(delta.z / hypotenuse) * (180 / PI);
	float yaw = atan2(delta.y, delta.x) * (180 / PI);
	if (pitch >= -89 && pitch <= 89 && yaw >= -180 && yaw <= 180)
	{
		if (viewAngles->x < pitch)
		{
			viewAngles->x += 0.1f;
		}
		else if (viewAngles->x > pitch)
		{
			viewAngles->x -= 0.1f;
		}

		if (viewAngles->y < yaw)
		{
			viewAngles->y += 0.1f;
		}
		else if (viewAngles->y > yaw)
		{
			viewAngles->y -= 0.1f;
		}
		//viewAngles->x = pitch;
		//viewAngles->y = yaw;
	}
}