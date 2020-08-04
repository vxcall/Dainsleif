#include "../pch.h"
#include "../LocalPlayer.h"
#include "AntiRecoil.h"

Vector3 oldPunch = { 0, 0, 0 };
int oldShotCount = 0;

void AntiRecoil::Run() {
    static const WeaponID rejectWeaponList[11] = {GLOCK_HG, DUAL_BERETTAS_HG, P250_HG, TEC9_HG,DESERT_EAGLE_HG,
                                                  NOVA_SG, XM1014_SG, SAWED_OFF_SG, SSG08_SR, AWP_SR, G3SG1_SR};
    LocalPlayer* lp = GetLocalPlayer();
    WeaponID currentWeaponID = lp->GetCurrentWeaponID();
    for (WeaponID rejW : rejectWeaponList) {
        if (rejW == currentWeaponID) {
            return;
        }
    }

    int* ShotCount = reinterpret_cast<int*>(*reinterpret_cast<uintptr_t*>(lp) + m_iShotsFired);

    if (*ShotCount >= 1) {
        if (*ShotCount != oldShotCount) {
            //This refers to the cursor position after local player shot. Bullet's gonna be shot out over the cursor by twice.
            auto *AimPunchAngle = reinterpret_cast<Vector3 *>(*reinterpret_cast<uintptr_t *>(lp) + m_aimPunchAngle);
            static auto engineModule = reinterpret_cast<uintptr_t>(GetModuleHandle("engine.dll"));
            auto *viewAngle = reinterpret_cast<Vector3 *>((*reinterpret_cast<uintptr_t *>((engineModule + dwClientState)) + dwClientState_ViewAngles));
            Vector3 rcsAngle{};
            rcsAngle.y = viewAngle->y + (oldPunch.y - AimPunchAngle->y * 2.f);
            rcsAngle.x = viewAngle->x + (oldPunch.x - AimPunchAngle->x * 2.f);

            viewAngle->Normalize();

            oldPunch.y = AimPunchAngle->y * 2.f;
            oldPunch.x = AimPunchAngle->x * 2.f;
            viewAngle->y = rcsAngle.y;
            viewAngle->x = rcsAngle.x;
            oldShotCount = *ShotCount;
        }
    } else {
        oldPunch = {0, 0, 0};
        oldShotCount = 0;
    }
}