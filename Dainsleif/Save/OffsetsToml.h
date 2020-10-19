#pragma once
#include "../pch.h"
#include <map>
#include <future>
#include "SettingsToml.h"
#include "../PatternScanner.h"

namespace OffsetsToml {
    std::map<std::string, uintptr_t> ReadOffsets(std::string& filename);
    void UpdateOffsets(std::string& filename);
    void InitializeOffsets(std::string& filename);
}
