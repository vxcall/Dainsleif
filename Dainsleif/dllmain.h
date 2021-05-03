#pragma once

#include "Save/SettingsToml.h"
#include "Save/OffsetsToml.h"
#include "Hacks/Aimbot.h"
#include "Hacks/Glow.h"
#include "Hacks/AntiRecoil.h"
#include "Hacks/Triggerbot.h"
#include "Hacks/AntiAFK.h"
#include "Hacks/MinimapHack.h"
#include "Hacks/Bunnyhop.h"
#include "Save/TabStateToml.h"
#include <thread>

#define DEBUG

#ifdef DEBUG
#define LOGHEX(name, val) std::cout << name << ": " << std::hex << val << std::endl;
#define LOG(x) std::cout << x << std::endl;
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
#define LOGFLAGS(flags)
#define ALLOCCONSOLE()
#define FREECONSOLE()
#endif

namespace HackFlags {
    extern bool bQuit, bAimbot, bGlowHack, bAntiRecoil, bTriggerBot, bBunnyhop, bAntiAFK, bMinimapHack;
}

namespace TabFlags {
    extern bool t_aimBot, t_glowHack, t_antiRecoil, t_triggerBot, t_bunnyHop, t_antiAFK, t_fov, t_esp, t_minimapHack;
}

extern bool g_ShowMenu;

int loadSettingsFiles();