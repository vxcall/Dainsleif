#include "../pch.h"
#include "../Player.h"
#include "AntiRecoil.h"

Vector3 oldPunch = { 0, 0, 0 };
int oldShotCount = 0;

void AntiRecoil::Run() {
    static const WeaponID rejectWeaponList[19] = { KNIFE, C4, GN_DECOY, GN_FLASH_, GN_HE, GN_MOLOTOV, GN_SMOKE, HG_GLOCK, HG_DUAL_BERETTAS, HG_P250, HG_TEC9,HG_DESERT_EAGLE,
                                                  SG_NOVA, SG_XM1014, SG_SAWED_OFF, SR_SSG08, SR_AWP, SR_G3SG1 };
    Player* localPlayer = Player::GetLocalPlayer();
    Weapon* activeWeapon = localPlayer->GetActiveWeapon();
    WeaponID activeWeaponID = activeWeapon->GetWeaponID();
    for (WeaponID rejW : rejectWeaponList) {
        if (rejW == activeWeaponID) {
            return;
        }
    }

    int shotCount = localPlayer->GetShotsFired();

    if (shotCount >= 1) {
        if (shotCount != oldShotCount) {
            //This refers to the cursor position after local player shot. Bullet's gonna be shot out over the cursor by twice.
            Vector3 aimPunchAngle = localPlayer->GetAimPunchAngle();
            Vector3* viewAngle = reinterpret_cast<Vector3*>(*reinterpret_cast<uintptr_t*>(Modules::engine + dwClientState) + dwClientState_ViewAngles);
            Vector3 rcsAngle{};
            rcsAngle.y = viewAngle->y + (oldPunch.y - aimPunchAngle.y * 2.f);
            rcsAngle.x = viewAngle->x + (oldPunch.x - aimPunchAngle.x * 2.f);

            viewAngle->Normalize();

            oldPunch.y = aimPunchAngle.y * 2.f;
            oldPunch.x = aimPunchAngle.x * 2.f;
            viewAngle->y = rcsAngle.y;
            viewAngle->x = rcsAngle.x;
            oldShotCount = shotCount;
        }
    }
    else {
        oldPunch = { 0, 0, 0 };
        oldShotCount = 0;
    }
}