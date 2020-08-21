#pragma once

namespace RWtoml {
    void ReadSettings(std::string& filename);
    void WriteSettings(std::string& filename);
    std::vector<uintptr_t> ReadOffsets(std::string& filename);
    void UpdateOffsets(std::string& filename);
    void InitializeOffsets(std::string& filename);
}