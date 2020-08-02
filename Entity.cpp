#include "pch.h"
#include "Entity.h"

extern uintptr_t moduleBase;

Vector3* Entity::GetBodyPosition()
{
	return reinterpret_cast<Vector3*>((*reinterpret_cast<uintptr_t*>(this) + m_vecOrigin));
}

Vector3* Entity::GetViewOffset()
{
	return reinterpret_cast<Vector3*>((*reinterpret_cast<uintptr_t*>(this) + m_vecViewOffset));
}

#define boneID 8
extern bool isTriggerBotON;
Vector3* Entity::GetBonePosition()
{
	uintptr_t boneMatrix = *reinterpret_cast<uintptr_t*>(*reinterpret_cast<uintptr_t*>(this) + m_dwBoneMatrix);
	if (!boneMatrix) { //When started the game while bAimbot is on, the game is gonna crash.
	    return nullptr;
	}
	static Vector3 bonePos;
    bonePos.x = *reinterpret_cast<float*>(boneMatrix + 0x30 * boneID + 0x0C);
    bonePos.y = *reinterpret_cast<float*>(boneMatrix + 0x30 * boneID + 0x1C);
    bonePos.z = *reinterpret_cast<float*>(boneMatrix + 0x30 * boneID + 0x2C);
	if (isTriggerBotON)
    {
        bonePos.z -= 2.f;
    }
	return &bonePos;
}

bool* Entity::IsDormant()
{
	return reinterpret_cast<bool*>((*(uintptr_t*)this + m_bDormant));
}

int* Entity::GetHealth()
{
	return reinterpret_cast<int*>((*(uintptr_t*)this + m_iHealth));
}

int Entity::GetTeam()
{
	return *reinterpret_cast<int*>((*(uintptr_t*)this + m_iTeamNum));
}

uintptr_t Entity::GetGlowIndex()
{
	return *reinterpret_cast<uintptr_t*>(*(uintptr_t*)this + m_iGlowIndex);
}

uintptr_t GetGlowObjectManager() {
	return *reinterpret_cast<uintptr_t*>(moduleBase + dwGlowObjectManager);
}

std::vector<Entity*> GetEntities()
{
	int maxnum = *GetMaxEntities(); //getting possible maximum number of entity. It was 64 when I tested.
	std::vector<Entity*> entityList; //initialize vector by specifying the size with maxnum, and fill them with 0.
	for (int i = 1; i < maxnum; ++i)
	{
		Entity* entity = reinterpret_cast<Entity*>(((moduleBase + dwEntityList) + i * 0x10));
		if (!*reinterpret_cast<uintptr_t*>(entity)) //Cast the address that possibly is entity into uintptr_t and check if it's null.
		    continue;
		entityList.push_back(entity);
	}
	return entityList;
}

int* GetMaxEntities() {
	uintptr_t moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandle("engine.dll"));
	return reinterpret_cast<int*>((*reinterpret_cast<uintptr_t*>((moduleBase + dwClientState)) + dwClientState_MaxPlayer));
}