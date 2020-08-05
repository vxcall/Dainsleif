#include "../pch.h"
#include "../Entity.h"
#include "../LocalPlayer.h"
#include "Triggerbot.h"

extern uintptr_t moduleBase;
extern bool bAimbot;

void Triggerbot::Run(std::vector<Entity*> entityList)
{
    static bool bFreeMouse;
    auto* fa = reinterpret_cast<uintptr_t *>(moduleBase + dwForceAttack);
    LocalPlayer* lp = GetLocalPlayer();
    int crosshairID = *reinterpret_cast<int*>(*reinterpret_cast<uintptr_t*>(lp) + m_iCrosshairId);
    if (crosshairID != 0) {
        //When you kill all enemy, it's somehow gonna be a number more than 300.
        if (crosshairID < 2 ||crosshairID - 2 > 9) return;
        if (lp->GetTeam() != entityList[crosshairID - 2]->GetTeam())
        {
            bFreeMouse = false;
            if (*fa == 4) {
                    Sleep(35);
                *fa = 5;
            } else if (*fa == 5) {
                *fa = 4;
            }
        }
    }
    if (crosshairID == 0 && !bFreeMouse) {
        *fa = 4;
        bFreeMouse = true;
    }
}