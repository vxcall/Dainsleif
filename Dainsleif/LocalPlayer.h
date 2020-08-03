#pragma once
#include "pch.h"
#include "Entity.h"

class LocalPlayer : public Entity
{
	//The values are quickly shifting each seconds, so I'm not supposed to store them to member variables.
	//Extract the real values by reading memory each time with member functions instead. The same applies to Entity class.
public:
	//GetHeadPosition calculates head position by view offset and body position.
	Vector3* GetHeadPosition();

    void SetFOV(int fov);
};

//GetLocalPlayer returns LocalPlayer class instance.
LocalPlayer* GetLocalPlayer();

