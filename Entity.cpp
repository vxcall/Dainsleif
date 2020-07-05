#include "pch.h"
#include "Entity.h"
#include "offsets.h"
#include "utility.h"
#include <iostream>
#include <vector>

Vector3* Entity::GetBodyPosition()
{
	return (Vector3*)(*(uintptr_t*)this + m_vecOrigin);
}

Vector3* Entity::GetViewOffset()
{
	return (Vector3*)(*(uintptr_t*)this + m_vecViewOffset);
}

#define boneID 8

Vector3* Entity::GetBonePosition()
{
	uint32_t boneMatrix = *(uint32_t*)(*(uint32_t*)this + m_dwBoneMatrix);
	static Vector3 bonePos;
	bonePos.x = *(float*)(boneMatrix + 0x30 * boneID + 0x0C);
	bonePos.y = *(float*)(boneMatrix + 0x30 * boneID + 0x1C);
	bonePos.z = *(float*)(boneMatrix + 0x30 * boneID + 0x2C);
	return &bonePos;
}

int* Entity::GetTeam()
{
	return (int*)(*(uintptr_t*)this + m_iTeamNum);
}

std::vector<Entity*> GetEntities(uintptr_t moduleBase)
{
	int maxnum = *GetMaxEntities(); //getting possible maximum number of entity. It was 64 when I tested.
	std::vector<Entity*> entityList; //initialize vector by specifying the size with maxnum, and fill them with 0.
	for (int i = 1; i < maxnum; i++)
	{
		Entity* entity = (Entity*)((moduleBase + dwEntityList) + i * 0x10);
		if (!*(uintptr_t*)entity) continue; //Cast the address that possibly is entity into uintptr_t and check if it's 0.
		entityList.push_back(entity);
	}
	return entityList;
}

int* GetMaxEntities() {
	uintptr_t moduleBase = (uintptr_t)GetModuleHandle(TEXT("engine.dll"));
	return (int*)(*(uintptr_t*)(moduleBase + dwClientState) + dwClientState_MaxPlayer);
}