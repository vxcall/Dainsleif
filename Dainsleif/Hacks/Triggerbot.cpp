#include "../pch.h"
#include "Triggerbot.h"

extern bool bAimbot;

void Triggerbot::Run()
{
    static bool bFreeMouse;
    auto* forceAttack = reinterpret_cast<uintptr_t*>(Modules::client + dwForceAttack);
    Player* localPlayer = Player::GetLocalPlayer();
    int crosshairID = localPlayer->GetCrosshairID();
    if (crosshairID != 0) {
        //When you kill all enemy, it's somehow gonna be a number more than 300.
        //if (crosshairID < 2 ||crosshairID - 2 > 9) return;
        Entity* target = Entity::GetByIndex(crosshairID - 1);
        if (target->GetClientClass()->m_ClassID == ClassID::CCSPlayer && localPlayer->GetTeam() != target->Cast<Player*>()->GetTeam())
        {
            bFreeMouse = false;
            if (*forceAttack == 4) {
                Sleep(35);
                *forceAttack = 5;
            }
            else if (*forceAttack == 5) {
                *forceAttack = 4;
            }
        }
    }
    if (crosshairID == 0 && !bFreeMouse) {
        *forceAttack = 4;
        bFreeMouse = true;
    }
}