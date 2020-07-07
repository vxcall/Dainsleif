#include "pch.h"
#include "Entity.h"
#include "LocalPlayer.h"

Vector3* Entity::GetBodyPosition()
{
	return reinterpret_cast<Vector3*>((*reinterpret_cast<uintptr_t*>(this) + m_vecOrigin));
}

Vector3* Entity::GetViewOffset()
{
	return reinterpret_cast<Vector3*>((*reinterpret_cast<uintptr_t*>(this) + m_vecViewOffset));
}

#define boneID 8

Vector3* Entity::GetBonePosition()
{
	uintptr_t boneMatrix = *reinterpret_cast<uintptr_t*>((*reinterpret_cast<uintptr_t*>(this) + m_dwBoneMatrix));
	static Vector3 bonePos;
	bonePos.x = *reinterpret_cast<float*>((boneMatrix + 0x30 * boneID + 0x0C));
	bonePos.y = *reinterpret_cast<float*>((boneMatrix + 0x30 * boneID + 0x1C));
	bonePos.z = *reinterpret_cast<float*>((boneMatrix + 0x30 * boneID + 0x2C));
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

uintptr_t GetGlowObjectManager(uintptr_t moduleBase) {
	return *reinterpret_cast<uintptr_t*>(moduleBase + dwGlowObjectManager);
}



void Entity::Glow(uintptr_t moduleBase)
{
	uintptr_t glowObjectManager = GetGlowObjectManager(moduleBase);
	uintptr_t glowIndex = this->GetGlowIndex();
	LocalPlayer* lp = GetLocalPlayer(moduleBase);
	int teamNum = this->GetTeam();
	if (!lp || !glowObjectManager)
	{
		std::cout << "Error has occurred in Glow function. NULL POINTER EXCEPTION" << std::endl;
		return;
	}
	if (teamNum == lp->GetTeam())
	{
		*(float*)(glowObjectManager + ((glowIndex * 0x38) + 0x4)) = 0.f;
		*(float*)(glowObjectManager + ((glowIndex * 0x38) + 0x8)) = 0.f;
		*(float*)(glowObjectManager + ((glowIndex * 0x38) + 0xC)) = 1.f;
		*(float*)(glowObjectManager + ((glowIndex * 0x38) + 0x10)) = 1.7f;
	}
	else if (teamNum != lp->GetTeam() && !*this->IsDormant())
	{
		*(float*)(glowObjectManager + ((glowIndex * 0x38) + 0x4)) = 1.f;
		*(float*)(glowObjectManager + ((glowIndex * 0x38) + 0x8)) = 0.f;
		*(float*)(glowObjectManager + ((glowIndex * 0x38) + 0xC)) = 0.f;
		*(float*)(glowObjectManager + ((glowIndex * 0x38) + 0x10)) = 1.7f;
	}
	*(bool*)(glowObjectManager + ((glowIndex * 0x38) + 0x24)) = true; //If I set this to false, the entire glow disappear
	*(bool*)(glowObjectManager + ((glowIndex * 0x38) + 0x25)) = false; //if i set this true, the damage indicater go out of the outline.
}

std::vector<Entity*> GetEntities(uintptr_t moduleBase)
{
	int maxnum = *GetMaxEntities(); //getting possible maximum number of entity. It was 64 when I tested.
	std::vector<Entity*> entityList; //initialize vector by specifying the size with maxnum, and fill them with 0.
	for (int i = 1; i < maxnum; ++i)
	{
		Entity* entity = reinterpret_cast<Entity*>(((moduleBase + dwEntityList) + i * 0x10));
		if (!*(uintptr_t*)entity) continue; //Cast the address that possibly is entity into uintptr_t and check if it's 0.
		entityList.push_back(entity);
	}
	return entityList;
}





int* GetMaxEntities() {
	uintptr_t moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandle(L"engine.dll"));
	return reinterpret_cast<int*>((*reinterpret_cast<uintptr_t*>((moduleBase + dwClientState)) + dwClientState_MaxPlayer));
}