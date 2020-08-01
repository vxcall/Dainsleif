#include "pch.h"
#include "LocalPlayer.h"
#include "GraphicHook.h"

uintptr_t moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandle("client.dll"));

bool bQuit = false, bAimbot, bGlowHack, bAntiRecoil, bTriggerBot;
int fov;
extern float aimSmoothness; //declared in LocalPlayer.cpp
ImVec4 enemyGlowColor, localGlowColor;

TCHAR dir[ MAX_PATH ];
std::string filename;//const char* dir = "C:/Users/PC/HACK4CSGO"; //directory that savedata will be saved.

extern bool g_ShowMenu; //decleard in GraphicHook.cpp

const double PI = 3.14159265358;
Entity* GetClosestEnemyFromCrosshair(std::vector<Entity*> entityList)
{
    static uintptr_t engineModule = reinterpret_cast<uintptr_t>(GetModuleHandle("engine.dll"));
    float closestDistance = 1000000;
    int closestEntityIndex = -1;
    LocalPlayer* lp = GetLocalPlayer(moduleBase);
    Vector3* viewAngles = reinterpret_cast<Vector3*>((*reinterpret_cast<uintptr_t*>((engineModule + dwClientState)) + dwClientState_ViewAngles));
    for (int i = 0; i < static_cast<int>(entityList.size()); ++i)
    {
        if (entityList[i]->GetTeam() == lp->GetTeam())
            continue;
        Vector3 delta;

        Vector3* entityHeadPosition = entityList[i]->GetBonePosition();
        if (!entityHeadPosition) continue; //null pointer check

        GetDistance(*entityHeadPosition, *lp->GetHeadPosition(), delta);
        float yaw = atan2(delta.y, delta.x) * (180 / static_cast<float>(PI));
        int yawDistance = abs(static_cast<int>(yaw - viewAngles->y));

        if (yawDistance < closestDistance) {
            closestDistance = yawDistance;
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
    bAimbot = toml::find_or<bool>(saveData, "bAimbot", false);
    aimSmoothness = toml::find_or<float>(saveData, "aimSmoothness", 0.2f);
    bGlowHack = toml::find_or<bool>(saveData, "bGlowHack", false);
    bAntiRecoil = toml::find_or<bool>(saveData, "bAntiRecoil", false);
    bTriggerBot = toml::find_or<bool>(saveData, "bTriggerBot", false);
    fov = toml::find_or<int>(saveData, "fov", 90);

    auto& enemyGlowColorTable = toml::find_or(saveData, "enemyGlowColor", {});
    enemyGlowColor = ImVec4(toml::find_or<float>(enemyGlowColorTable, "Red", 0.8f), toml::find_or<float>(enemyGlowColorTable, "Green", 0.1f), toml::find_or<float>(enemyGlowColorTable, "Blue", 0.15f), toml::find_or<float>(enemyGlowColorTable, "Alpha", 1.0f));

    auto& localGlowColorTable = toml::find_or(saveData, "localGlowColor", {});
    localGlowColor = ImVec4(toml::find_or<float>(localGlowColorTable, "Red", 0.0f), toml::find_or<float>(localGlowColorTable, "Green", 0.255f), toml::find_or<float>(localGlowColorTable, "Blue", 0.7f), toml::find_or<float>(localGlowColorTable, "Alpha", 1.0f));
}

void WriteFile() {
    //Make a variable holds keys and values.
    const toml::value data{{"bAimbot", bAimbot}, {"bGlowHack", bGlowHack},
                           {"bAntiRecoil", bAntiRecoil}, {"bTriggerBot", bTriggerBot},
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

    std::filesystem::path path{filename};
    std::filesystem::create_directories(path.parent_path());
    if (!std::filesystem::exists(path))
    {
        std::ofstream stream{path};
        stream.close();
    }

    ParseFile();

    hookEndScene();

    std::vector<Entity*> entityList;

    while (true)
    {
        static bool isStayingMainMenu = false;

        if (bQuit)
        {
            WriteFile();
            break;
        }

        int gameState = *reinterpret_cast<int*>((*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(GetModuleHandle("engine.dll")) + dwClientState) + dwClientState_State));

        if (gameState != 6) {
            if (!isStayingMainMenu)
            {
                WriteFile();
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
                    WriteFile();
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
            Entity* closestEnt = GetClosestEnemyFromCrosshair(entityList);
            if (closestEnt != nullptr && !*closestEnt->IsDormant())
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