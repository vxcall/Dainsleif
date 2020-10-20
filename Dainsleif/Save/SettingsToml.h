#pragma once
#include <map>
#include "../pch.h"
#include "../PatternScanner.h"
#include "../dllmain.h"
#include "../Hook/GraphicHook.h"

namespace SettingsToml {
    void Fetch(std::string& filename);
    void Save(std::string& filename);
}