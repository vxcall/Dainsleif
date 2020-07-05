#pragma once
#include <Windows.h>
#include "vector3.h"
#include <vector>

class Entity
{
public:
	Vector3* GetBodyPosition();
	Vector3* GetViewOffset();
	Vector3* GetBonePosition();
	int* GetTeam();
};

std::vector<Entity*> GetEntities(uintptr_t moduleBase);

int* GetMaxEntities();

