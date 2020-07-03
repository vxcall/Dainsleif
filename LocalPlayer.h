#pragma once
#include <Windows.h>
#include "vector3.h"

class LocalPlayer
{
	//The values are quickly shifting each seconds, so I'm not supposed to store them to member variables.
	//Extract the real values by reading memory each time with member functions instead.
public:
	static LocalPlayer* GetLocalPlayer(uintptr_t moduleBase);
	Vector3* GetBodyPosition();
	Vector3* GetViewOffset();
	Vector3* GetHeadPosition();
	int* GetHealth();
};

