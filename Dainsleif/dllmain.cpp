#include "pch.h"
#include "RWtoml.h"
#include "Hacks/Aimbot.h"
#include "Hacks/Glow.h"
#include "Hacks/AntiRecoil.h"
#include "Hacks/Triggerbot.h"
#include "Hook/GraphicHook.h"
#include "PatternScanner.h"
#include "Hacks/AntiAFK.h"
#include <thread>

bool bQuit, bAimbot, bGlowHack, bAntiRecoil, bTriggerBot, bAntiAFK;
int fov;
bool g_ShowMenu = false;
bool inGame = false;

std::string settingsFile;
std::string offsetsFile;

VOID WINAPI Detach()
{
    unhookEndScene();

    fclose(stdout);
    FreeConsole();
}

void InitSetting() {
    Player::GetLocalPlayer()->SetFOV(fov);
}

DWORD WINAPI fMain(LPVOID lpParameter)
{
    //Create console window
    AllocConsole();
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);

    TCHAR dir[ MAX_PATH ];
    SHGetSpecialFolderPath(NULL, dir, CSIDL_COMMON_DOCUMENTS, 0); //Find the Document directory location
    settingsFile = static_cast<std::string>(dir) + "/Dainsleif/savedata.toml"; //Set file path.
    offsetsFile = static_cast<std::string>(dir) + "/Dainsleif/offsets.toml";
    std::filesystem::path path1{settingsFile}, path2{offsetsFile};
    std::filesystem::create_directories(path1.parent_path());
    if (!std::filesystem::exists(path1))
    {
        std::ofstream stream{path1};
        stream.close();
    }

    if (!std::filesystem::exists(path2))
    {
        std::ofstream stream{path2};
        stream.close();
        RWtoml::InitializeOffsets(offsetsFile);
    }

    RWtoml::ReadSettings(settingsFile);
    RWtoml::ReadOffsets(offsetsFile);

    Modules::Initialize();

    dwClientState = PatternScanner("engine.dll", "\xA1????\x8B?????\x85?\x74?\x8B?", 1).CalculateOffset(Modules::engine, 0);

    std::cout << "client.dll: " << std::hex << Modules::client << std::endl;
    std::cout << "engine.dll: " << std::hex << Modules::engine << std::endl;

    hookEndScene();

    std::vector<Player*> playerList;

    //MUST save this to use as a flag cuz the value of local player's gonna be stored at the same address even the match ended.
    Player* oldLocalPlayer = nullptr;

    //Hack loop entry point.
    while (true)
    {
        if (GetAsyncKeyState(VK_DELETE) & 1 || bQuit)
        {
            RWtoml::WriteSettings(settingsFile);
            break;
        }

        int gameState = *reinterpret_cast<int*>(*reinterpret_cast<uintptr_t*>(Modules::engine + dwClientState) + dwClientState_State);

        Player* localPlayer = Player::GetLocalPlayer();

        if (gameState != 6 && inGame) {   //Not 6 means user's in menu.//true means user used to be in game.
            RWtoml::WriteSettings(settingsFile);
            oldLocalPlayer = localPlayer;
            inGame = false;
        }

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            g_ShowMenu = !g_ShowMenu;
            if (!g_ShowMenu)
                RWtoml::WriteSettings(settingsFile);
        }

        if (gameState != 6 || !localPlayer || localPlayer == oldLocalPlayer)
            continue;

        if (!localPlayer->GetActiveWeapon())
            continue;

        //If we have values to set in initializing phase, have to be written here.
        if (!inGame) {
            InitSetting();
            inGame = true;
        }

        if (bTriggerBot || bGlowHack || bAntiRecoil) {
            playerList = Player::GetAll();
        }

        if (bTriggerBot)
        {
            Triggerbot::Run();
        }

        if (bAimbot)
        {
            std::vector<Player*> pl = Player::GetLiving();
            Aimbot::Run(pl);
        }

        if (bGlowHack)
        {
            for (Player* player : playerList)
            {
                Glow::Run(player);
            }
        }

        if (bAntiRecoil)
        {
            AntiRecoil::Run();
        }

        static bool checkState_bAntiAFK;
        if (!checkState_bAntiAFK && bAntiAFK) { //First loop after user ticks the checkbox.
            std::thread worker(AntiAFK::Run, &bAntiAFK);
            worker.detach();
            checkState_bAntiAFK = true;
        } else if (checkState_bAntiAFK && !bAntiAFK) { //First loop after user unticks the checkbox.
            checkState_bAntiAFK = false;
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
        Detach();
    }
    return TRUE;
}