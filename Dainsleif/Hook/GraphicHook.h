#pragma once
#include "../pch.h"
#include "ImGuiTheme.h"
#include "GraphicHook.h"
#include "DrawGUI.h"
#include <map>

namespace HackFlags {
    extern bool bEsp, bLineOverlay, bRectOverlay;
}

struct WindowSize {
    int w;
    int h;
};

void InitializeGraphicHook();
void ShutDownGraphicHook();

extern std::map<std::string, bool> visibleHacks;