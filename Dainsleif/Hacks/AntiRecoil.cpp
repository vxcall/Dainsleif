#include "../pch.h"
#include "../LocalPlayer.h"
#include "AntiRecoil.h"


Vector3 oldPunch = { 0, 0, 0 };
int oldShotCount = 0;

void AntiRecoil::Run() {
    static uintptr_t engineModule = reinterpret_cast<uintptr_t>(GetModuleHandle("engine.dll"));
    LocalPlayer* lp = GetLocalPlayer();
    int* ShotCount = reinterpret_cast<int*>(*reinterpret_cast<uintptr_t*>(lp) + m_iShotsFired);

    if (*ShotCount >= 1) {
        if (*ShotCount != oldShotCount) {
            //This refers to the cursor position after local player shot. Bullet's gonna be shot out over the cursor by twice.
            Vector3 *AimPunchAngle = reinterpret_cast<Vector3 *>(*reinterpret_cast<uintptr_t *>(lp) + m_aimPunchAngle);
            Vector3 *viewAngle = reinterpret_cast<Vector3 *>((*reinterpret_cast<uintptr_t *>((engineModule + dwClientState)) + dwClientState_ViewAngles));
            Vector3 rcsAngle;
            rcsAngle.y = viewAngle->y + (oldPunch.y - AimPunchAngle->y * 2.f);
            rcsAngle.x = viewAngle->x + (oldPunch.x - AimPunchAngle->x * 2.f);

            while (viewAngle->y > 180)
                viewAngle->y -= 360;
            while (viewAngle->y < -180)
                viewAngle->y += 360;

            if (viewAngle->x > 89.f)
                viewAngle->x = 89.f;
            else if (viewAngle->x < -89.f)
                viewAngle->x = -89.f;

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