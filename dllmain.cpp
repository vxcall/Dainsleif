#include "pch.h"
#include "LocalPlayer.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "detours.h"
//#include "MinHook.h"

using endScene = HRESULT (__stdcall*)(IDirect3DDevice9* pDevice);
endScene originalEndScene = nullptr; //An original endscene which is null now.

LPD3DXFONT font;
HRESULT __stdcall hookedEndScene(IDirect3DDevice9* pDevice) { //A function containing a bunch of rendering process, that is gonna be hooked.
    //now here we can create our own graphics
    int padding = 2;
    int rectx1 = 100, rectx2 = 300, recty1 = 50, recty2 = 100;
    D3DRECT rectangle = { rectx1, recty1, rectx2, recty2 };
    pDevice->Clear(1, &rectangle, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 0, 0, 0), 0.0f, 0); // this draws a rectangle
    if (!font)
        D3DXCreateFont(pDevice, 16, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);
    RECT textRectangle;
    SetRect(&textRectangle, rectx1 + padding, recty1 + padding, rectx2 - padding, recty2 - padding);
    font->DrawText(NULL, "Press END key to exit", -1, &textRectangle, DT_NOCLIP | DT_LEFT, D3DCOLOR_ARGB(255, 153, 255, 153)); //draw text;
    return originalEndScene(pDevice);
}

void hookEndScene() {
    IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (!pD3D) return;

    D3DPRESENT_PARAMETERS d3dparams = {0};  //set D3DPRESENT_PARAMETERS to pass itself as an argument of createDevice().
    d3dparams.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dparams.hDeviceWindow = GetForegroundWindow();
    d3dparams.Windowed = true;  //need to be interchangeable

    IDirect3DDevice9* pDevice = nullptr; //A variable to be a device in the next line.

    HRESULT result = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetForegroundWindow(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dparams, &pDevice);
    if (FAILED(result) || !pDevice){
        std::cout << "Device is null" << std::endl;
        pD3D->Release();
        return;
    }

    void** vTable = *reinterpret_cast<void***>(pDevice);
    originalEndScene = (endScene)DetourFunction((PBYTE)vTable[42],(PBYTE)hookedEndScene);
    pDevice->Release();
    pD3D->Release();
}

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

DWORD __CLRCALL_PURE_OR_STDCALL fMain(HMODULE hMod)
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    hookEndScene();
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
            if (bAimbot) {
                std::cout << "Aimbot is on" << std::endl;
            } else {
                std::cout << "Aimbot is off" << std::endl;
            }
        }

        if (GetAsyncKeyState(VK_DELETE) & 1)
        {
            entityList = GetEntities(moduleBase);
            bGlowHack = !bGlowHack;
            if (bGlowHack) {
                std::cout << "Glow hack is on" << std::endl;
            } else {
                std::cout << "Glow hack is off" << std::endl;
            }
        }

        if (GetAsyncKeyState(VK_HOME) & 1)
        {
            entityList = GetEntities(moduleBase);
            bNoRecoil = !bNoRecoil;

            if (bNoRecoil) {
                std::cout << "Neutralize Recoil is on" << std::endl;
            } else {
                std::cout << "Neutralize Recoil is off" << std::endl;
            }

        }

        if (GetAsyncKeyState(VK_PRIOR) & 1)
        {
            entityList = GetEntities(moduleBase);
            bTriggerBot = !bTriggerBot;

            if (bTriggerBot) {
                std::cout << "Trigger bot is on" << std::endl;
            } else {
                std::cout << "Trigger bot is off" << std::endl;
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

