#include "../pch.h"
#include "../LocalPlayer.h"
#include "Glow.h"

ImVec4 enemyGlowColor, localGlowColor;

void Glow::Run(Entity* entity)
{
    uintptr_t glowObjectManager = GetGlowObjectManager();
    uintptr_t glowIndex = entity->GetGlowIndex();
    GlowObject go(glowObjectManager, glowIndex);

    LocalPlayer* lp = GetLocalPlayer();

    int teamNum = entity->GetTeam();

    if (teamNum == lp->GetTeam())
    {
        *go.Red = localGlowColor.x;
        *go.Green = localGlowColor.y;
        *go.Blue = localGlowColor.z;
        *go.Alpha = localGlowColor.w;
    }
    else if (teamNum != lp->GetTeam() && !*entity->IsDormant())
    {
        *go.Red = enemyGlowColor.x;
        *go.Green = enemyGlowColor.y;
        *go.Blue = enemyGlowColor.z;
        *go.Alpha = enemyGlowColor.w;
    }
    *(bool*)(glowObjectManager + ((glowIndex * 0x38) + 0x24)) = true; //If I set this to false, the entire glow disappear
    *(bool*)(glowObjectManager + ((glowIndex * 0x38) + 0x25)) = false; //if i set this true, the damage indicater go out of the outline.
}