#pragma once
#include <Windows.h>
#include "vector3.h"

class LocalPlayer
{
	//The values are quickly shifting each seconds, so I'm not supposed to store them to member variables.
	//Extract the real values by reading memory each time with member functions instead. The same applies to Entity class.
public:
	//GetBodyPosition retrieves where local player's body is as vector3.
	Vector3* GetBodyPosition();

	//GetViewOffset returns the distance between the body position and the actual sight of local player.
	Vector3* GetViewOffset();

	//GetHeadPosition calculates head position by view offset and body position.
	Vector3* GetHeadPosition();

	//GetDistance returns distance between local player and target passed as argument.
	float GetDistance(Vector3 targetPos, Vector3& deltaVector);

	//GetHealth retrieves local player's health.
	int* GetHealth();

	//GetTeam returns teamNumber so that I can distinguish either the entity is friendly or hostile.
	int* GetTeam();

	//AimBot lets local player aim at enemy's head with full precision.
	void AimBot(Vector3 TargetsHeadPosition);
};

//GetLocalPlayer returns LocalPlayer class instance.
LocalPlayer* GetLocalPlayer(uintptr_t moduleBase);

