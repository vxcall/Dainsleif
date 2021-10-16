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
    GlowObject* glowObject = reinterpret_cast<GlowObject*>(glowObjectManager + (glowIndex * sizeof(GlowObject)));

    Player* localPlayer = Player::GetLocalPlayer();

    int teamNum = player->GetTeam();

    if (teamNum == localPlayer->GetTeam())
    {
        glowObject->r = localGlowColor.x;
        glowObject->g = localGlowColor.y;
        glowObject->b = localGlowColor.z;
        glowObject->a = localGlowColor.w;
    }
    else if (teamNum != localPlayer->GetTeam() && !player->IsDormant())
    {
        glowObject->r = enemyGlowColor.x;
        glowObject->g = enemyGlowColor.y;
        glowObject->b = enemyGlowColor.z;
        glowObject->a = enemyGlowColor.w;
    }
    glowObject->m_bRenderWhenOccluded = true; //If I set this to false, the entire glow disappear
    glowObject->m_bRenderWhenUnoccluded = false; //if i set this true, the damage indicater go out of the outline.
}