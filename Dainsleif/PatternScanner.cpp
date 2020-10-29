#include "PatternScanner.h"
#include <optional>

//FindPattern expects an input like this -> \x0F\x11\x05????\x83\xC8\x01
//For example: BB [0C45572F] 83 FF 01 -> offset should be 1. offset has to be the number of byte before address we need.
std::optional<uintptr_t> PatternScanner::FindPattern()
{
    HMODULE hModule = GetModuleHandle(this->moduleName);
    if (!hModule)
        return std::nullopt;
    MODULEINFO moduleInfo;
    if (!GetModuleInformation(GetCurrentProcess(), hModule, &moduleInfo, sizeof(moduleInfo)))
        return std::nullopt;

    auto beginningOfModule = static_cast<const char*>(moduleInfo.lpBaseOfDll);
    const auto end = beginningOfModule + moduleInfo.SizeOfImage; //This is the last element of beginningOfModule array.

    auto current = beginningOfModule;
    auto patternCopy = this->pattern;

    while (current < end && *patternCopy) {
        //*current refers to the each element of current array and basically cycle through the char array to check if they are matched.
        if (*current == *patternCopy || *patternCopy == '?') {
            ++current;
            ++patternCopy;
        } else {
            current = ++beginningOfModule; //increment beginningOfModule value and assign to current
            patternCopy = this->pattern; //"pattern" variable holds the original value of pattern.
        }
    }

    // If nothing found, return optional containing nothing
    if (beginningOfModule == end){
        return std::nullopt;
    }

    //back to the address of where current was located by subtracting the length of original pattern.
    current -= strlen(this->pattern);

    return *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(current) + this->offset);
}

//Sometimes desired pointer is not illustrated in the module, so find an address which is located near desired one, and add extra bytes to reach the address.
uintptr_t PatternScanner::CalculateOffset(uintptr_t base, int extra) {
    std::optional<uintptr_t> o_pattern = FindPattern();
    if (o_pattern) {
        return o_pattern.value() - base + extra;
    } else {
        return 0000000;
    }
}