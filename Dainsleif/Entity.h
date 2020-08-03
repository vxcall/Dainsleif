#pragma once
#include "pch.h"

class Entity
{
public:
	//GetBodyPosition retrieves where entity's body is as vector3.
	Vector3* GetBodyPosition();

	//GetViewOffset returns the distance between the body position and the actual sight of entity.
	Vector3* GetViewOffset();

	//GetHealth retrieves local player's health.
	int GetHealth();

	//GetTeam returns teamNumber so that I can distinguish either the entity is friendly or hostile.
	int GetTeam();

	bool* IsDormant();

	Vector3* GetBonePosition();

	uintptr_t GetGlowIndex();
};

std::vector<Entity*> GetEntities();

int* GetMaxEntities();

