#pragma once
#include "../Hook/GraphicHook.h"
#include "../pch.h"

namespace TabState {
    void Save(std::string& filename);
    void Fetch(std::string& filename);
}