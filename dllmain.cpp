#include "pch.h"
#include "LocalPlayer.h"


uintptr_t moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandle("client.dll"));

Entity* GetClosestEnemy(std::vector<Entity*> entityList)
{
    LocalPlayer* lp = GetLocalPlayer(moduleBase);

    float closestDistance = 1000000;
    int closestEntityIndex = -1;

    for (unsigned int i = 0; i < entityList.size(); ++i)
    {
        if (entityList[i]->GetTeam() == lp->GetTeam()) continue; //filter out if entity is same team as local player.
        if (*entityList[i]->GetHealth() < 1 || *lp->GetHealth() < 1) continue; //skip if either entity or local player is dead

        float currentDistance = lp->GetDistance(*(entityList[i]->GetBodyPosition()));

        if (currentDistance < closestDistance) //if this entity is closer than old one, then update closestDistance and closestEntityIndex.
        {
            closestDistance = currentDistance;
            closestEntityIndex = i;
        }
    }
    if (closestEntityIndex == -1)
    {
        return nullptr;
    }
    return entityList[closestEntityIndex]; //return closest Entity pointer.
}

DWORD fMain(HMODULE hMod)
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    bool bAimbot = false, bGlowHack = false, bNoRecoil = false, bTriggerBot = false;

    std::vector<Entity*> entityList;

    //waiting key input for cheats
    while (true)
    {
        if (GetAsyncKeyState(VK_END) & 1) break;

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            entityList = GetEntities(moduleBase);
            bAimbot = !bAimbot;

            switch (bAimbot)
            {
            case true:
                std::cout << "Aimbot is on" << std::endl;
                break;
            case false:
                std::cout << "Aimbot is off" << std::endl;
                break;
            }
        }

        if (GetAsyncKeyState(VK_DELETE) & 1)
        {
            entityList = GetEntities(moduleBase);
            bGlowHack = !bGlowHack;
            switch (bGlowHack)
            {
            case true:
                std::cout << "Glow hack is on" << std::endl;
                break;
            case false:
                std::cout << "Glow hack is off" << std::endl;
                break;
            }
        }

        if (GetAsyncKeyState(VK_HOME) & 1)
        {
            entityList = GetEntities(moduleBase);
            bNoRecoil = !bNoRecoil;

            switch (bNoRecoil)
            {
            case true:
                std::cout << "Neutralize Recoil is on" << std::endl;
                break;
            case false:
                std::cout << "Neutralize Recoil is off" << std::endl;
                break;
            }
        }

        if (GetAsyncKeyState(VK_PRIOR) & 1)
        {
            entityList = GetEntities(moduleBase);
            bTriggerBot = !bTriggerBot;

            switch (bTriggerBot)
            {
                case true:
                    std::cout << "Trigger bot is on" << std::endl;
                    break;
                case false:
                    std::cout << "Trigger bot is off" << std::endl;
                    break;
            }
        }

        if (bAimbot)
        {
            Entity* closestEnt = GetClosestEnemy(entityList);
            if (closestEnt && !*closestEnt->IsDormant())
            {
                    GetLocalPlayer(moduleBase)->AimBot(*closestEnt->GetBonePosition());
            }
        }

        if (bGlowHack)
        {
            for (unsigned int i = 0; i < entityList.size(); ++i)
            {
                entityList[i]->Glow(moduleBase);
            }
        }

        if (bNoRecoil)
        {
            LocalPlayer* lp = GetLocalPlayer(moduleBase);
            lp->NeutralizeRecoil();
        }

        if (bTriggerBot)
        {
            LocalPlayer* lp = GetLocalPlayer(moduleBase);
            if (lp)
            {
                lp->AutoPullTrigger(entityList);
            }
        }

        Sleep(1); //sleep for performance aspect
    }

    FreeLibraryAndExitThread(hMod, 0);
    return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)fMain, hModule, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

