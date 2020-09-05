#pragma once
#include "imgui.h"


namespace Default {
    //Aimbot
    const bool bAimbot = false;
    const float aimSmoothness = 0.2f;
    const float range = 10.f;

    //Glow hack
    const bool bGlowhack = false;
    const ImVec4 enemyGlowColor = ImVec4(0.8f,0.1f,0.15f,1.f);
    const ImVec4 localGlowColor = ImVec4(0.f,0.255f,0.7f,1.f);

    //Anti Recoil
    const bool bAntiRecoil = false;

    //Trigger bot
    const bool bTriggerBot = false;

    //FOV
    const int fov = 90;

    //Anti AFK
    const bool bAntiAFK = false;

    //ESP
    const bool bEsp = false;
    const bool bLineOverlay = false;
    const bool bRectOverlay = false;
}