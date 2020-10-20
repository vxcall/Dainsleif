#pragma once
#include "../pch.h"
#include <map>
#include <future>
#include "SettingsToml.h"
#include "../PatternScanner.h"

namespace OffsetsToml {
    std::map<std::string, uintptr_t> Fetch(std::string& filename);
    void Update(std::string& filename);
    void Initialize(std::string& filename);
}
