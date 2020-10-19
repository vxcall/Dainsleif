#pragma once
#include "../Hook/GraphicHook.h"
#include "../pch.h"
#include "../dllmain.h"

namespace TabStateToml {
    void Save(std::string& filename);
    void Fetch(std::string& filename);
}