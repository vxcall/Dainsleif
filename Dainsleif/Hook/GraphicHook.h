#pragma once
#include "../pch.h"
#include "ImGuiTheme.h"
#include "GraphicHook.h"
#include "DrawGUI.h"
#include <map>


struct WindowSize {
    int w;
    int h;
};

void hookEndScene();
void unhookEndScene();

extern std::map<std::string, bool> visibleHacks;
extern bool t_aimBot, t_glowHack, t_antiRecoil, t_triggerBot, t_antiAFK, t_fov, t_esp, t_minimapHack;