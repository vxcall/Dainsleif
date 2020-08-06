#include "../pch.h"
#include "../Entity.h"
#include "../LocalPlayer.h"
#include "Triggerbot.h"

extern uintptr_t moduleBase;
extern bool bAimbot;

void Triggerbot::Run(std::vector<Entity*> entityList)
{
    //if bFreeMouse is false, mouse move will set to be free.
    static bool bFreeMouse;

    LocalPlayer* lp = GetLocalPlayer();
    int crosshairID = *reinterpret_cast<int*>(*reinterpret_cast<uintptr_t*>(lp) + m_iCrosshairId);
    auto* fa = reinterpret_cast<uintptr_t *>(moduleBase + dwForceAttack);
    //check if you're aiming at living hostile.
    if (crosshairID > 1 && crosshairID - 2 < (static_cast<int>(entityList.size()) + 1) && lp->GetTeam() != entityList[crosshairID - 2]->GetTeam()) {
        bFreeMouse = false;
        if (bAimbot && *fa == 4)
            Sleep(60);
        *fa = 5;
    }

    if (crosshairID == 0 && !bFreeMouse) {
        *fa = 4;
        bFreeMouse = true;
    }
}