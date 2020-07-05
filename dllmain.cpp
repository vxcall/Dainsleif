// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"
#include <Windows.h>
#include "offsets.h"
#include "LocalPlayer.h"
#include "Entity.h"
#include <iostream>


uintptr_t moduleBase = (uintptr_t)GetModuleHandle(TEXT("client.dll"));

Entity* GetClosestEnemy(std::vector<Entity*> entityList)
{
    LocalPlayer* lp = GetLocalPlayer(moduleBase);

    float closestDistance = 1000000;
    int closestEntityIndex = -1;

    for (unsigned int i = 0; i < entityList.size(); i++)
    {
        if (*entityList[i]->GetTeam() == *lp->GetTeam()) continue; //filter out if entity is same team as local player.
        if (*entityList[i]->GetHealth() < 1 || *lp->GetHealth() < 1) continue; //skip if either entity or local player is dead

        float currentDistance = lp->GetDistance(*(entityList[i]->GetBonePosition()));

        if (currentDistance < closestDistance) //if this entity is closer than old one, then update closestDistance and closestEntityIndex.
        {
            std::cout << "currentDistance: " << currentDistance << std::endl;
            std::cout << "closestEntityIndex: " << closestEntityIndex << std::endl;
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

    //waiting key input for cheats
    while (true)
    {
        if (GetAsyncKeyState(VK_END) & 1) break;
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            std::cout << "INSERT pressed" << std::endl;
            while (1)
            {
                if (GetAsyncKeyState(VK_DELETE) & 1)
                {
                    std::cout << "DELETE pressed" << std::endl;
                    break;
                }

                Entity* closestEnt = GetClosestEnemy(GetEntities(moduleBase));

                if (!closestEnt) continue;
                if (closestEnt)
                {
                    GetLocalPlayer(moduleBase)->AimBot(*closestEnt->GetBonePosition());
                }
                Sleep(1);
            }
        }
        
        
        Sleep(1);
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

