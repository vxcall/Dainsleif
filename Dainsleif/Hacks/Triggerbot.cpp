#include "../pch.h"
#include "../Entity.h"
#include "../LocalPlayer.h"
#include "Triggerbot.h"

extern uintptr_t moduleBase;

//If Trigger bot is on, Aimbot have to need this somehow.
void Triggerbot::Run(std::vector<Entity*> entityList)
{
    uintptr_t* fa = reinterpret_cast<uintptr_t *>(moduleBase + dwForceAttack);
    LocalPlayer* lp = GetLocalPlayer();
    int crosshairID = *reinterpret_cast<int*>(*reinterpret_cast<uintptr_t*>(lp) + m_iCrosshairId); //this int value holds index of entity list.
    if (crosshairID != 0) {
        //When you kill all enemy, it's somehow gonna be a number more than 300.
        if (crosshairID < 2 ||crosshairID - 2 > 9) return;
        if (lp->GetTeam() != entityList[crosshairID - 2]->GetTeam())
        {
            std::cout << *fa << std::endl;
            if (*fa == 4) {
                *fa = 5;
            } else if (*fa == 5) {
                *fa = 4;
            }
        }
    } else if (!crosshairID) {
        *fa = 4;
    }
}