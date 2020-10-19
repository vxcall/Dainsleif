#pragma once
#include "../pch.h"
#include "ImGuiTheme.h"
#include "GraphicHook.h"
#include "DrawGUI.h"
#include <map>

namespace EspFlags {
    extern bool bEsp, bLineOverlay, bRectOverlay;
}

struct WindowSize {
    int w;
    int h;
};

void hookEndScene();
void unhookEndScene();

extern std::map<std::string, bool> visibleHacks;