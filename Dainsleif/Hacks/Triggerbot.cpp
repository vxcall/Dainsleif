#include "../pch.h"
#include "Triggerbot.h"

extern bool bAimbot;

void Triggerbot::Run()
{
    //if bFreeMouse is false, mouse move will set to be free.
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
            if (bAimbot && *forceAttack == 4)
            {
                Sleep(60);
            }
            *forceAttack = 5;
        }
    }

    if (crosshairID == 0 && !bFreeMouse) {
        *forceAttack = 4;
        bFreeMouse = true;
    }
}