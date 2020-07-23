#include "pch.h"
#include "LocalPlayer.h"
#include "GraphicHook.h"


bool bQuit = false, bAimbot = false, bGlowHack = false, bNoRecoil = false, bTriggerBot = false;

extern bool g_ShowMenu;

uintptr_t moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandle("client.dll"));

Entity* GetClosestEnemy(std::vector<Entity*> entityList)
{
    LocalPlayer* lp = GetLocalPlayer(moduleBase);

    float closestDistance = 1000000;
    int closestEntityIndex = -1;

    for (int i = 0; i < static_cast<int>(entityList.size()); ++i)
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

HMODULE g_hModule;

DWORD __stdcall EjectThread(LPVOID lpParameter)
{
    Sleep(100);
    FreeLibraryAndExitThread(g_hModule, 0);
}

DWORD WINAPI fMain()
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    hookEndScene();
    std::vector<Entity*> entityList = {};
    //waiting key input for cheats
    while (true)
    {
        if (bQuit)
            break;

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            int gameState = *reinterpret_cast<int*>((*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(GetModuleHandle("engine.dll")) + dwClientState) + dwClientState_State)); //6 means user's in game.
            if ( gameState== 6 && GetLocalPlayer(moduleBase))
                g_ShowMenu = !g_ShowMenu;
        }

        if (bAimbot || bTriggerBot || bGlowHack || bNoRecoil) {
            entityList = GetEntities(moduleBase);
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
    fclose(f);
    FreeConsole();
    CreateThread(0, 0, EjectThread, 0, 0, 0);
    return 0;
}





BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        g_hModule = hModule;
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)fMain, 0, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

