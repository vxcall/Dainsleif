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
    //For example: BB [0C45572F] 83 FF 01 -> offset should be 1. offset has to be the number of byte before address we need.
    PatternScanner(char* moduleName, const char* pattern, int offset)
    : moduleName(moduleName), pattern(pattern), offset(offset)
    {}

    uintptr_t CalculateOffset(uintptr_t base);
};