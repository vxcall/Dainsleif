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
	int* GetHealth();

	//GetTeam returns teamNumber so that I can distinguish either the entity is friendly or hostile.
	int GetTeam();

	bool* IsDormant();

	Vector3* GetBonePosition();

	uintptr_t GetGlowIndex();

	void Glow(uintptr_t moduleBase);
};

//This is a struct to treat glow stuff cleaner maybe XD.
struct GlowObject {
    float* Red;
    float* Green;
    float* Blue;
    float* Alpha;


    GlowObject(uintptr_t glowObjectManager, uintptr_t glowIndex)
    {
        Red = reinterpret_cast<float*>((glowObjectManager + ((glowIndex * 0x38) + 0x4)));
        Green = reinterpret_cast<float*>((glowObjectManager + ((glowIndex * 0x38) + 0x8)));
        Blue = reinterpret_cast<float*>((glowObjectManager + ((glowIndex * 0x38) + 0xC)));
        Alpha = reinterpret_cast<float*>((glowObjectManager + ((glowIndex * 0x38) + 0x10)));
    }
};

uintptr_t GetGlowObjectManager(uintptr_t moduleBase);

std::vector<Entity*> GetEntities(uintptr_t moduleBase);

int* GetMaxEntities();

