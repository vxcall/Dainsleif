#include "pch.h"
#include "LocalPlayer.h"
#include "GraphicHook.h"

bool bQuit = false, bAimbot = false, bGlowHack = false, bNoRecoil = false, bTriggerBot = false;

const char* dir = "C:/Users/PC/HACK4CSGO"; //directory that savedata will be saved.
std::string filename = (std::string)dir + "/savedata.toml"; //Set file path.

extern bool g_ShowMenu; //decleard in GraphicHook.cpp
int fov = 90;

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

void ParseFile() {
    auto saveData = toml::parse(filename);

    // find specified values associated with one keys, and assign them into each variable.
    bAimbot = toml::find<bool>(saveData, "bAimbot");
    bGlowHack = toml::find<bool>(saveData, "bGlowHack");
    bNoRecoil = toml::find<bool>(saveData, "bNoRecoil");
    bTriggerBot = toml::find<bool>(saveData, "bTriggerBot");
    fov = toml::find<int>(saveData, "fov");
}

void WriteFile() {
    //Make a variable holds keys and values.
    const toml::value data{{"bAimbot", bAimbot}, {"bGlowHack", bGlowHack},
                           {"bNoRecoil", bNoRecoil}, {"bTriggerBot", bTriggerBot},
                           {"fov", fov}};

    //Open file and write it in toml syntax.
    std::ofstream file;
    file.open(filename, std::ios::out);
    file << data;
    file.close();
}

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

    std::ifstream fs(filename);
    if (!fs.is_open()) {
        _mkdir(dir);
    } else {
        ParseFile();
    }

    hookEndScene();

    std::vector<Entity*> entityList = {};
    //waiting key input for cheats
    while (true)
    {
        static bool isStayingMainMenu = false;

        if (bQuit)
        {
            WriteFile();
            break;
        }

        int gameState = *reinterpret_cast<int*>((*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(GetModuleHandle("engine.dll")) + dwClientState) + dwClientState_State));

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            if (gameState== 6 && *reinterpret_cast<uintptr_t*>(GetLocalPlayer(moduleBase))) //6 means user's in game.
            {
                isStayingMainMenu = false;
                g_ShowMenu = !g_ShowMenu;
                if (!g_ShowMenu)
                    WriteFile();
            }
        }

        if (gameState != 6) {
            if (!isStayingMainMenu)
            {
                WriteFile();
                isStayingMainMenu = true;
            }
            g_ShowMenu = false;
        }

        if (!*reinterpret_cast<uintptr_t*>(GetLocalPlayer(moduleBase))) continue;

        static bool bInitLocalPlayer = false;
        if (!bInitLocalPlayer) {
            GetLocalPlayer(moduleBase)->SetFOV(fov);
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