#pragma once

#include "Save/SettingsToml.h"
#include "Save/OffsetsToml.h"
#include "Hacks/Aimbot.h"
#include "Hacks/Glow.h"
#include "Hacks/AntiRecoil.h"
#include "Hacks/Triggerbot.h"
#include "Hacks/AntiAFK.h"
#include "Hacks/MinimapHack.h"
#include "Save/TabStateToml.h"
#include <thread>

namespace HackFlags {
    extern bool bQuit, bAimbot, bGlowHack, bAntiRecoil, bTriggerBot, bAntiAFK, bMinimapHack;
}

namespace TabFlags {
    extern bool t_aimBot, t_glowHack, t_antiRecoil, t_triggerBot, t_antiAFK, t_fov, t_esp, t_minimapHack;
}

extern bool g_ShowMenu;

int loadSettingsFiles();