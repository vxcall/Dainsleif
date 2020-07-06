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

int EucledeanAlgorithm(int var1, int var2) {
	var1 = abs(var1);
	var2 = abs(var2);
	if (var1 == var2) {
		return var1;
	}

	if (var1 < var2)
	{
		std::swap(var1, var2);
	}

	std::vector<int> nr;
	int reminder = var1 % var2;
	if (!reminder)
	{
		return var2;
	}
	nr.push_back(reminder);
	int nullcheck = var2 % reminder;
	if (!nullcheck)
	{
		return reminder;
	}
	nr.push_back(nullcheck);
	int i = 1;
	while (1) {
		nr.push_back(nr[i - 1] % nr[i]);
		++i;
		if (nr[i] == 0) break;
	}
	return nr[i - 1];
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

	std::cout << "aaa" << std::endl;

	if (pitch >= -89 && pitch <= 89 && yaw >= -180 && yaw <= 180)
	{
		int pitchDistance = static_cast<int>(pitch - viewAngles->x);
		int yawDistance = static_cast<int>(yaw - viewAngles->y);
		pitchDistance = abs(pitchDistance);
		yawDistance = abs(yawDistance);

		if (pitchDistance <= 0.4f) { //If distance between vertical axis of crosshair and enemy's head is below 0.4 which is pretty close, just aim at exact head.
			viewAngles->x = pitch;
		}
		else 
		{
			if (viewAngles->x < pitch)  //my view is smaller than pitch.
			{
				viewAngles->x += 0.5f;
			}
			else if (viewAngles->x > pitch)
			{
				viewAngles->x -= 0.5f;
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
					viewAngles->y -= 0.5f;
				}
				else
				{
					viewAngles->y += 0.5f;
				}

			}
			else if (viewAngles->y > yaw)
			{
				if (sign(viewAngles->y) == 1 && sign(yaw) == -1 && viewAngles->y >= 90)  //When yaw is like -170 and viewAngle steps over 180
				{
					viewAngles->y += 0.5f;
				}
				else
				{
					viewAngles->y -= 0.5f;
				}

			}
		}
	}
}