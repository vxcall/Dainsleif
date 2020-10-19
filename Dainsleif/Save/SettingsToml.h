#pragma once
#include <map>
#include "../pch.h"
#include "../PatternScanner.h"
#include "../dllmain.h"
#include "../Hook/GraphicHook.h"

namespace SettingsToml {
    void ReadSettings(std::string& filename);
    void WriteSettings(std::string& filename);
}