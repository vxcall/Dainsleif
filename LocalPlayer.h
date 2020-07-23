#pragma once
#include "vector3.h"
#include "Entity.h"
#include <cmath>

class LocalPlayer : public Entity
{
	//The values are quickly shifting each seconds, so I'm not supposed to store them to member variables.
	//Extract the real values by reading memory each time with member functions instead. The same applies to Entity class.
public:
	//GetHeadPosition calculates head position by view offset and body position.
	Vector3* GetHeadPosition();

	//GetDistance returns distance between local player and target passed as argument.
	float GetDistance(Vector3 targetPos, Vector3& deltaVector);

	float GetDistance(Vector3 targetPos);

	//AimBot lets local player aim at enemy's head with full precision.
	void AimBot(Vector3 TargetsHeadPosition);

	void NeutralizeRecoil();

    void AutoPullTrigger(std::vector<Entity*> entityList);

    void SetFOV(int fov);
};

//GetLocalPlayer returns LocalPlayer class instance.
LocalPlayer* GetLocalPlayer(uintptr_t moduleBase);

