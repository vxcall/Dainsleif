#include "dllmain.h"
#include "pch.h"
#include "Hook/ControlCursor.h"
#include "Interfaces/CInterfaceList.h"

//#define DEBUG

#ifdef DEBUG
#define LOGHEX(name, val) std::cout << name << ": " << std::hex << val << std::endl;
#define ALLOCCONSOLE()\
{\
    AllocConsole();\
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);\
}
#define FREECONSOLE()\
{\
    fclose(stdout);\
    FreeConsole();\
}
#else
#define LOGHEX(name, val)
#define ALLOCCONSOLE()
#define FREECONSOLE()
#endif

namespace HackFlags
{
    bool bQuit, bAimbot, bGlowHack, bAntiRecoil, bTriggerBot, bAntiAFK, bMinimapHack;
}

namespace TabFlags
{
    bool t_aimBot = true, t_glowHack = true, t_antiRecoil = true, t_triggerBot = true, t_antiAFK, t_fov, t_esp, t_minimapHack;
}

int fov;
bool g_ShowMenu = false;
bool inGame = false;

std::string settingsFile;
std::string offsetsFile;
std::string tabStateFile;

VOID WINAPI Detach ( )
{
    unhookEndScene ( );
    FREECONSOLE ( );
}

void InitSetting ( )
{
    Player::GetLocalPlayer ( )->SetFOV ( fov );
}

std::map< std::string, bool > visibleHacks;

DWORD WINAPI fMain ( LPVOID lpParameter )
{
    ALLOCCONSOLE ( );
    TCHAR dir[ MAX_PATH ];
    SHGetSpecialFolderPath ( NULL, dir, CSIDL_COMMON_DOCUMENTS, 0 ); //Find the Document directory location
    settingsFile = static_cast< std::string > ( dir ) + "/Dainsleif/savedata.toml"; //Set file path.
    offsetsFile = static_cast< std::string > ( dir ) + "/Dainsleif/offsets.toml";
    tabStateFile = static_cast< std::string > ( dir ) + "/Dainsleif/tabstate.toml";
    std::filesystem::path path1{ settingsFile }, path2{ offsetsFile }, path3{ tabStateFile };
    std::filesystem::create_directories ( path1.parent_path ( ) );
    if ( !std::filesystem::exists ( path1 ) )
    {
        std::ofstream stream{ path1 };
        stream.close ( );
    }

    if ( !std::filesystem::exists ( path2 ) )
    {
        std::ofstream stream{ path2 };
        stream.close ( );
        OffsetsToml::Initialize ( offsetsFile );
    }

    if ( !std::filesystem::exists ( path3 ) )
    {
        std::ofstream stream{ path3 };
        stream.close ( );
    }

    SettingsToml::Fetch ( settingsFile );
    OffsetsToml::Fetch ( offsetsFile );
    TabStateToml::Fetch ( tabStateFile );

    visibleHacks = {
        { "Aim Bot", TabFlags::t_aimBot },
        { "Glow Hack", TabFlags::t_glowHack },
        { "Anti Recoil", TabFlags::t_antiRecoil },
        { "Trigger Bot", TabFlags::t_triggerBot },
        { "Anti AFK", TabFlags::t_antiAFK },
        { "Fov", TabFlags::t_fov },
        { "Esp", TabFlags::t_esp },
        { "Minimap Hack", TabFlags::t_minimapHack }
    };

    Modules::Initialize ( );

    dwClientState = PatternScanner ( "engine.dll", "\xA1????\x8B?????\x85?\x74?\x8B?", 1 ).CalculateOffset ( Modules::engine, 0 );

    LOGHEX ( "client.dll", Modules::client );
    LOGHEX ( "engine.dll", Modules::engine );

    g_csgo.Initialize ( );

    hookEndScene ( );
    HookLockCursor ( );

    std::vector< Player* > playerList;

    //MUST save this to use as a flag cuz the value of local player's gonna be stored at the same address even the match ended.
    Player* oldLocalPlayer = nullptr;

    //Hack loop entry point.
    while ( true )
    {
        if ( GetAsyncKeyState ( VK_DELETE ) & 1 || HackFlags::bQuit )
        {
            SettingsToml::Save ( settingsFile );
            TabStateToml::Save ( tabStateFile );
            break;
        }

        int gameState = *reinterpret_cast< int* > ( *reinterpret_cast< uintptr_t* > ( Modules::engine + dwClientState ) + dwClientState_State );

        Player* localPlayer = Player::GetLocalPlayer ( );

        if ( gameState != 6 && inGame )
        {   //Not 6 means user's in menu.//true means user used to be in game.
            SettingsToml::Save ( settingsFile );
            TabStateToml::Save ( tabStateFile );
            oldLocalPlayer = localPlayer;
            inGame = false;
        }

        if ( GetAsyncKeyState ( VK_INSERT ) & 1 )
        {
            g_ShowMenu = !g_ShowMenu;
            if ( !g_ShowMenu )
            {
                SettingsToml::Save ( settingsFile );
                TabStateToml::Save ( tabStateFile );
            }
        }

        if ( gameState != 6 || !localPlayer || localPlayer == oldLocalPlayer )
            continue;

        if ( !localPlayer->GetActiveWeapon ( ) )
            continue;

        //If we have values to set in initializing phase, have to be written here.
        if ( !inGame )
        {
            InitSetting ( );
            inGame = true;
        }

        if ( HackFlags::bTriggerBot || HackFlags::bGlowHack || HackFlags::bAntiRecoil )
        {
            playerList = Player::GetAll ( );
        }

        if ( HackFlags::bTriggerBot )
        {
            Triggerbot::Run ( );
        }

        if ( HackFlags::bAimbot )
        {
            std::vector< Player* > pl = Player::GetLivingOpponents ( );
            Aimbot::Run ( pl );
        }

        if ( HackFlags::bGlowHack )
        {
            for ( Player* player : playerList )
            {
                Glow::Run ( player );
            }
        }

        if ( HackFlags::bAntiRecoil )
        {
            AntiRecoil::Run ( );
        }

        if ( HackFlags::bMinimapHack )
        {
            std::vector< Player* > pl = Player::GetLivingOpponents ( );
            Minimap::Run ( pl );
        }

        static bool checkState_bAntiAFK;
        if ( !checkState_bAntiAFK && HackFlags::bAntiAFK )
        { //First loop after user ticks the checkbox.
            std::thread worker ( AntiAFK::Run, &HackFlags::bAntiAFK );
            worker.detach ( );
            checkState_bAntiAFK = true;
        }
        else if ( checkState_bAntiAFK && !HackFlags::bAntiAFK )
        { //First loop after user unticks the checkbox.
            checkState_bAntiAFK = false;
        }

        Sleep ( 1 ); //sleep for performance aspect
    }

    FreeLibraryAndExitThread ( static_cast< HMODULE > ( lpParameter ), EXIT_SUCCESS );
}

BOOL APIENTRY DllMain ( HMODULE hModule, DWORD dwReason, LPVOID lpReserved )
{
    if ( dwReason == DLL_PROCESS_ATTACH )
    {
        DisableThreadLibraryCalls ( hModule );

        HANDLE hThread = CreateThread ( nullptr, 0, fMain, hModule, 0, nullptr );
        if ( hThread )
        {
            CloseHandle ( hThread );
        }
    }
    else if ( dwReason == DLL_PROCESS_DETACH && !lpReserved )
    {
        Detach ( );
    }
    return TRUE;
}
