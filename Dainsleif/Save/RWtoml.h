#pragma once

#include <map>

namespace RWtoml {
    void ReadSettings(std::string& filename);
    void WriteSettings(std::string& filename);
    std::map<std::string, uintptr_t> ReadOffsets(std::string& filename);
    void UpdateOffsets(std::string& filename);
    void InitializeOffsets(std::string& filename);
}