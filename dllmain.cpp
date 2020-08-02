#include "pch.h"
#include "RWtoml.h"
#include "Hacks/Aimbot.h"
#include "GraphicHook.h"

uintptr_t moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandle("client.dll"));

bool bQuit, bAimbot, bGlowHack, bAntiRecoil, bTriggerBot;
int fov;


TCHAR dir[ MAX_PATH ];
std::string filename;//const char* dir = "C:/Users/PC/Dainsleif"; //directory savedata will be saved.
extern bool g_ShowMenu; //decleard in GraphicHook.cpp



VOID WINAPI Detach(LPVOID lpParameter)
{
    unhookEndScene();

    fclose(stdout);
    FreeConsole();
}

DWORD WINAPI fMain(LPVOID lpParameter)
{
    //Create console window
    AllocConsole();
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);

    SHGetSpecialFolderPath(NULL, dir, CSIDL_COMMON_DOCUMENTS, 0); //Find the Document directory location
    filename = static_cast<std::string>(dir) + "/Dainsleif/savedata.toml"; //Set file path.

    std::filesystem::path path{filename};
    std::filesystem::create_directories(path.parent_path());
    if (!std::filesystem::exists(path))
    {
        std::ofstream stream{path};
        stream.close();
    }

    RWtoml::ParseFile(filename);

    hookEndScene();

    std::vector<Entity*> entityList;

    while (true)
    {
        static bool isStayingMainMenu = false;

        if (bQuit)
        {
            RWtoml::WriteFile(filename);
            break;
        }

        int gameState = *reinterpret_cast<int*>((*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(GetModuleHandle("engine.dll")) + dwClientState) + dwClientState_State));

        if (gameState != 6) {
            if (!isStayingMainMenu)
            {
                RWtoml::WriteFile(filename);
                isStayingMainMenu = true;
            }
            g_ShowMenu = false;
        }

        if (!*reinterpret_cast<uintptr_t*>(GetLocalPlayer(moduleBase))) continue;

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            if (gameState== 6 && *reinterpret_cast<uintptr_t*>(GetLocalPlayer(moduleBase))) //6 means user's in game.
            {
                isStayingMainMenu = false;
                g_ShowMenu = !g_ShowMenu;
                if (!g_ShowMenu)
                    RWtoml::WriteFile(filename);
            }
        }

        static bool bInitLocalPlayer = false;
        if (!bInitLocalPlayer) {
            GetLocalPlayer(moduleBase)->SetFOV(fov);
        }

        if (bAimbot || bTriggerBot || bGlowHack || bAntiRecoil) {
            entityList = GetEntities(moduleBase);
        }

        if (bAimbot)
        {
            LocalPlayer* lp = GetLocalPlayer(moduleBase);
            Aimbot::Run(entityList, lp);
        }

        if (bGlowHack)
        {
            for (unsigned int i = 0; i < entityList.size(); ++i)
            {
                entityList[i]->Glow(moduleBase);
            }
        }

        if (bAntiRecoil)
        {
            GetLocalPlayer(moduleBase)->NeutralizeRecoil();
        }

        if (bTriggerBot)
        {
            GetLocalPlayer(moduleBase)->AutoPullTrigger(entityList);
        }

        Sleep(1); //sleep for performance aspect
    }

    FreeLibraryAndExitThread(static_cast<HMODULE>(lpParameter), EXIT_SUCCESS);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);

        HANDLE hThread = CreateThread(nullptr, 0, fMain, hModule, 0, nullptr);
        if (hThread)
        {
            CloseHandle(hThread);
        }
    }
    else if (dwReason == DLL_PROCESS_DETACH && !lpReserved)
    {
        Detach(hModule);
    }
    return TRUE;
}