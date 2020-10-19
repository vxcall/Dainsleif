#include "../pch.h"
#include "Triggerbot.h"
#include "../dllmain.h"

void Triggerbot::Run()
{
    Player* localPlayer = Player::GetLocalPlayer();
    Weapon* weapon = localPlayer->GetActiveWeapon();
    WeaponID weaponId = weapon->GetWeaponID();
    static const WeaponID rejectWeaponList[8] = {KNIFE, C4, GN_DECOY, GN_FLASH_, GN_HE, GN_MOLOTOV, GN_SMOKE};
    for (auto& rejW : rejectWeaponList) {
        if (rejW == weaponId)
            return;
    }

    //if bFreeMouse is false, mouse move will set to be free.
    static bool bFreeMouse;
    auto* forceAttack = reinterpret_cast<int*>(Modules::client + dwForceAttack);

    int crosshairID = localPlayer->GetCrosshairID();
    if (crosshairID != 0) {
        //When you kill all enemy, it's somehow gonna be a number more than 300.
        Entity* target = Entity::GetByIndex(crosshairID - 1);
        if (target->GetClientClass()->m_ClassID == ClassID::CCSPlayer && localPlayer->GetTeam() != target->Cast<Player*>()->GetTeam())
        {
            bFreeMouse = false;
            if (HackFlags::bAimbot && *forceAttack == 4)
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