#include "../pch.h"
#include "Glow.h"

ImVec4 enemyGlowColor, localGlowColor;

uintptr_t GetGlowObjectManager() {
    return *reinterpret_cast<uintptr_t*>(Modules::client + dwGlowObjectManager);
}

void Glow::Run(Player* player)
{
    uintptr_t glowObjectManager = GetGlowObjectManager();
    uintptr_t glowIndex = player->GetGlowIndex();
    GlowObject go(glowObjectManager, glowIndex);

    Player* localPlayer = Player::GetLocalPlayer();

    int teamNum = player->GetTeam();

    if (teamNum == localPlayer->GetTeam())
    {
        *go.Red = localGlowColor.x;
        *go.Green = localGlowColor.y;
        *go.Blue = localGlowColor.z;
        *go.Alpha = localGlowColor.w;
    }
    else if (teamNum != localPlayer->GetTeam() && !player->IsDormant())
    {
        *go.Red = enemyGlowColor.x;
        *go.Green = enemyGlowColor.y;
        *go.Blue = enemyGlowColor.z;
        *go.Alpha = enemyGlowColor.w;
    }
    *reinterpret_cast<bool*>(glowObjectManager + (glowIndex * 0x38) + 0x24) = true; //If I set this to false, the entire glow disappear
    *reinterpret_cast<bool*>(glowObjectManager + (glowIndex * 0x38) + 0x25) = false; //if i set this true, the damage indicater go out of the outline.
}