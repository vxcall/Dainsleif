#include "pch.h"
#include "LocalPlayer.h"
#include "GraphicHook.h"

uintptr_t moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandle("client.dll"));

bool bQuit = false, bAimbot = false, bGlowHack = false, bNoRecoil = false, bTriggerBot = false;
int fov = 90;
extern float aimSmoothness; //declared in LocalPlayer.cpp
ImVec4 enemyGlowColor = ImVec4(0.8f,0.1f,0.15f,1.f);
ImVec4 localGlowColor = ImVec4(0.f,0.255f,0.7f,1.f);

TCHAR dir[ MAX_PATH ];
std::string filename;//const char* dir = "C:/Users/PC/HACK4CSGO"; //directory that savedata will be saved.

extern bool g_ShowMenu; //decleard in GraphicHook.cpp

Entity* GetClosestEnemy(std::vector<Entity*> entityList)
{
    LocalPlayer* lp = GetLocalPlayer(moduleBase);

    float closestDistance = 1000000;
    int closestEntityIndex = -1;

    for (int i = 0; i < static_cast<int>(entityList.size()); ++i)
    {
        if (entityList[i]->GetTeam() == lp->GetTeam()) continue; //filter out if entity is same team as local player.
        if (*entityList[i]->GetHealth() < 1 || *lp->GetHealth() < 1) continue; //skip if either entity or local player is dead

        float currentDistance = GetDistance(*entityList[i]->GetBodyPosition(), *lp->GetHeadPosition());

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

Entity* GetClosestEnemyFromCrosshair(std::vector<Entity*> entityList)
{
    float closestDistance = 1000000;
    int closestEntityIndex = -1;
    static uintptr_t engineModule = reinterpret_cast<uintptr_t>(GetModuleHandle("engine.dll"));
    Vector3* viewAngles = reinterpret_cast<Vector3*>((*reinterpret_cast<uintptr_t*>((engineModule + dwClientState)) + dwClientState_ViewAngles));
    for (int i = 0; i < static_cast<int>(entityList.size()); ++i)
    {
        float targetPosition = GetDistance(*entityList[i]->GetBodyPosition(), *viewAngles);
        if (targetPosition < closestDistance) {
            closestDistance = targetPosition;
            closestEntityIndex = i;
        }
    }
    if (closestEntityIndex == -1)
    {
        return nullptr;
    }
    return entityList[closestEntityIndex];
}

void ParseFile() {
    auto saveData = toml::parse(filename);

    // find specified values associated with one keys, and assign them into each variable.
    bAimbot = toml::find<bool>(saveData, "bAimbot");
    aimSmoothness = toml::find<float>(saveData, "aimSmoothness");
    bGlowHack = toml::find<bool>(saveData, "bGlowHack");
    bNoRecoil = toml::find<bool>(saveData, "bNoRecoil");
    bTriggerBot = toml::find<bool>(saveData, "bTriggerBot");
    fov = toml::find<int>(saveData, "fov");
    enemyGlowColor = ImVec4(toml::find<float>(saveData, "enemyGlowColor", "Red"), toml::find<float>(saveData, "enemyGlowColor", "Green"), toml::find<float>(saveData, "enemyGlowColor", "Blue"), toml::find<float>(saveData, "enemyGlowColor", "Alpha"));
    localGlowColor = ImVec4(toml::find<float>(saveData, "localGlowColor", "Red"), toml::find<float>(saveData, "localGlowColor", "Green"), toml::find<float>(saveData, "localGlowColor", "Blue"), toml::find<float>(saveData, "localGlowColor", "Alpha"));
}

void WriteFile() {
    //Make a variable holds keys and values.
    const toml::value data{{"bAimbot", bAimbot}, {"bGlowHack", bGlowHack},
                           {"bNoRecoil", bNoRecoil}, {"bTriggerBot", bTriggerBot},
                           {"fov", fov}, {"enemyGlowColor",    {{"Red", enemyGlowColor.x}, {"Green", enemyGlowColor.y}, {"Blue", enemyGlowColor.z}, {"Alpha", enemyGlowColor.w}}},
                           {"localGlowColor",    {{"Red", localGlowColor.x}, {"Green", localGlowColor.y}, {"Blue", localGlowColor.z}, {"Alpha", localGlowColor.w}}},
                           {"aimSmoothness", aimSmoothness}};
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
    SHGetSpecialFolderPath(NULL, dir, CSIDL_COMMON_DOCUMENTS, 0); //Find the Document directory location
    filename = static_cast<std::string>(dir) + "\\HACK4CSGO\\savedata.toml"; //Set file path.

    std::ifstream fs(filename); //check if the file is exsist or not
    if (!fs.is_open()) {
        _mkdir((static_cast<std::string>(dir) + "\\HACK4CSGO").c_str()); //convert dir variable which is typed TCHAR into std::string, then convert back to char*
        WriteFile();
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