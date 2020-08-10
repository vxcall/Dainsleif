#pragma once
#include <iostream>
#include <Windows.h>
#include <Psapi.h>

class PatternScanner {
    char* moduleName;
    const char* pattern;
    int offset;

    uintptr_t FindPattern();
public:
    PatternScanner(char* moduleName, const char* pattern, int offset)
    : moduleName(moduleName), pattern(pattern), offset(offset)
    {}
    uintptr_t CalculateOffset(uintptr_t base);
};