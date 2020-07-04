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

std::vector<Entity*> GetEntities(uintptr_t moduleBase)
{
	int maxnum = *GetMaxEntities(); //getting possible maximum number of entity. It was 64 when I tested.
	std::vector<Entity*> entityList(maxnum); //initialize vector by specifying the size with maxnum.
	for (unsigned int i = 0; i < maxnum; i++)
	{
		std::cout << i << std::endl;
		Entity* entity = (Entity*)((moduleBase + dwEntityList) + i * 0x10);
		entityList.push_back(entity);
	}
	return entityList;
}

int* GetMaxEntities() {
	uintptr_t moduleBase = (uintptr_t)GetModuleHandle(TEXT("engine.dll"));
	return (int*)(*(uintptr_t*)(moduleBase + dwClientState) + dwClientState_MaxPlayer);
}