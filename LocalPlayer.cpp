#include "pch.h"
#include "LocalPlayer.h"


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

Vector3* LocalPlayer::GetHeadPosition()
{
	Vector3 bp = *(this->GetBodyPosition()); //get position and dereference it to calculate later on.
	Vector3 vo = *(this->GetViewOffset()); //get viewoffset and dereference it to calculate later on.
	Vector3* headPosition = &(bp + vo); //calculate them and store the result into pointer variable.
	return headPosition;
}

int sign(float A) {
	return (A > 0) - (A < 0);
}

double PI = 3.14159265358;
void LocalPlayer::AimBot(Vector3 TargetsHeadPosition)
{
	static uintptr_t engineModule = reinterpret_cast<uintptr_t>(GetModuleHandle(L"engine.dll"));
	static Vector3* viewAngles = reinterpret_cast<Vector3*>((*reinterpret_cast<uintptr_t*>((engineModule + dwClientState)) + dwClientState_ViewAngles));
	Vector3 delta;
	float hypotenuse = GetDistance(TargetsHeadPosition, delta);
	float pitch = -asin(delta.z / hypotenuse) * (180 / static_cast<float>(PI));
	float yaw = atan2(delta.y, delta.x) * (180 / static_cast<float>(PI));

	if (pitch >= -89 && pitch <= 89 && yaw >= -180 && yaw <= 180)
	{
		int pitchDistance = abs(static_cast<int>(pitch - viewAngles->x));
		int yawDistance = abs(static_cast<int>(yaw - viewAngles->y));

		float num = 0.5f / max(pitchDistance, yawDistance);
		float x = num * min(pitchDistance, yawDistance);

		/*
		num * max == 0.5f.
		Bigger:0.5 = Smoller:x
		*/
		float pf;
		float yf;
		if (pitchDistance > yawDistance)
		{
			pf = 0.5f;
			yf = x;
		}
		else
		{
			pf = x;
			yf = 0.5f;
		}

		if (pitchDistance <= 0.4f) { //If distance between vertical axis of crosshair and enemy's head is below 0.4 which is pretty close, just aim at exact head.
			viewAngles->x = pitch;
		}
		else
		{
			if (viewAngles->x < pitch)  //my view is smaller than pitch.
			{
				viewAngles->x += pf;
			}
			else if (viewAngles->x > pitch)
			{
				viewAngles->x -= pf;
			}
		}

		if (yawDistance <= 0.4f) {
			viewAngles->y = yaw;
		}
		else
		{
			if (viewAngles->y < yaw)
			{
				if (sign(viewAngles->y) == -1 && sign(yaw) == 1 && viewAngles->y <= -90) //When yaw is like 170 and viewAngle steps over -180
				{
					viewAngles->y -= yf;
				}
				else
				{
					viewAngles->y += yf;
				}

			}
			else if (viewAngles->y > yaw)
			{
				if (sign(viewAngles->y) == 1 && sign(yaw) == -1 && viewAngles->y >= 90)  //When yaw is like -170 and viewAngle steps over 180
				{
					viewAngles->y += yf;
				}
				else
				{
					viewAngles->y -= yf;
				}

			}
		}
	}
}

Vector3 oldPunch = { 0, 0, 0 };
int oldShotCount = 0;

void LocalPlayer::NeutralizeRecoil()
{
	static uintptr_t engineModule = reinterpret_cast<uintptr_t>(GetModuleHandle(L"engine.dll"));

	int* ShotCount = reinterpret_cast<int*>(*reinterpret_cast<uintptr_t*>(this) + m_iShotsFired);

	if (*ShotCount >= 1)
	{
		if (*ShotCount != oldShotCount) {
			//This refers to the cursor position after local player shot. Bullet's gonna be shot out over the cursor by twice.
			Vector3* AimPunchAngle = reinterpret_cast<Vector3*>(*reinterpret_cast<uintptr_t*>(this) + m_aimPunchAngle);
			Vector3* viewAngle = reinterpret_cast<Vector3*>((*reinterpret_cast<uintptr_t*>((engineModule + dwClientState)) + dwClientState_ViewAngles));
			Vector3 rcsAngle;
			rcsAngle.y = viewAngle->y + (oldPunch.y - AimPunchAngle->y * 2);
			rcsAngle.x = viewAngle->x + (oldPunch.x - AimPunchAngle->x * 2);

			while (viewAngle->y > 180)
				viewAngle->y -= 360;
			while (viewAngle->y < -180)
				viewAngle->y += 360;

			if (viewAngle->x > 89.f)
				viewAngle->x = 89.f;
			else if (viewAngle->x < -89.f)
				viewAngle->x = -89.f;

			oldPunch.x = AimPunchAngle->x * 2;
			oldPunch.y = AimPunchAngle->y * 2;
			viewAngle->y = rcsAngle.y;
			viewAngle->x = rcsAngle.x;
			oldShotCount = *ShotCount;
		}
	}
	else
	{
		oldPunch = { 0, 0, 0 };
		oldShotCount = 0;
	}
}