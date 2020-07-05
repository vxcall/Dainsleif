#include "pch.h"
#include "LocalPlayer.h"
#include "offsets.h"
#include "utility.h"
#include <iostream>
#include <Windows.h>
#include "vector3.h"
#include <math.h>
#include <cmath>


LocalPlayer* GetLocalPlayer(uintptr_t moduleBase)
{
	LocalPlayer* lp = (LocalPlayer*)(moduleBase + dwLocalPlayer); //get local player address and cast it to my original class type
	return lp;
}

float LocalPlayer::GetDistance(Vector3 targetPos, Vector3& deltaVector)
{
    deltaVector = *(this->GetHeadPosition()) - targetPos; //minus operation is defined in vector3.h
	deltaVector.x = fabs(deltaVector.x);
	deltaVector.y = fabs(deltaVector.y);
	deltaVector.z = fabs(deltaVector.z);
	float distance = sqrt(deltaVector.x * deltaVector.x + deltaVector.y * deltaVector.y + deltaVector.z * deltaVector.z); //This is the trigonometry calculation to get hypnotenuse.
	return distance;
}

Vector3* LocalPlayer::GetBodyPosition()
{
	return (Vector3*)(*(uintptr_t*)this + m_vecOrigin);
}

Vector3* LocalPlayer::GetViewOffset()
{
	return (Vector3*)(*(uintptr_t*)this + m_vecViewOffset);
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
	return (int*)(*(uintptr_t*)this + m_iHealth);
}

int* LocalPlayer::GetTeam()
{
	return (int*)(*(uintptr_t*)this + m_iTeamNum);
}

double PI = 3.14159265358;
void LocalPlayer::AimBot(Vector3 TargetsHeadPosition)
{
	static uint32_t engineModule = (uint32_t)GetModuleHandle(TEXT("engine.dll"));
	static Vector3* viewAngles = (Vector3*)(*(uint32_t*)(engineModule + dwClientState) + dwClientState_ViewAngles);
	Vector3 delta;
	float hypotenuse = GetDistance(TargetsHeadPosition, delta);
	float pitch = -asin(delta.z / hypotenuse) * (180 / PI);
	float yaw = atan2(delta.y, delta.x) * (180 / PI);
	if (pitch >= -89 && pitch <= 89 && yaw >= -180 && yaw <= 180)
	{
		viewAngles->x = pitch;
		viewAngles->y = yaw;
	}
}