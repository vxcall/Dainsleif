#include <iostream>
#include <Windows.h>
#include <Psapi.h>

class PatternScanner {
public:
    template <typename T>
    static T* FindPattern(char* moduleName, const char* pattern, int offset);
};

//expect an input like this -> \x0F\x11\x05????\x83\xC8\x01
template <typename T>
T* PatternScanner::FindPattern(char* moduleName, const char* pattern, int offset)
{
    HMODULE hModule = GetModuleHandle(moduleName);
    if (!hModule)
        return 0;
    MODULEINFO moduleInfo;
    if (!GetModuleInformation(GetCurrentProcess(), hModule, &moduleInfo, sizeof(moduleInfo)))
        return 0;

    auto beginningOfModule = static_cast<const char*>(moduleInfo.lpBaseOfDll);
    const auto end = beginningOfModule + moduleInfo.SizeOfImage; //This is the last element of beginningOfModule array.

    auto current = beginningOfModule;
    auto patternCopy = pattern;

    while (current < end && *patternCopy) {
        //*current refers to the each element of current array and basically cycle through the char array to check if they are matched.
        if (*current == *patternCopy || *patternCopy == '?') {
            ++current;
            ++patternCopy;
        } else {
            current = ++beginningOfModule; //increment beginningOfModule value and assign to current
            patternCopy = pattern; //"pattern" variable holds the original value of pattern.
        }
    }

    //rewind the address of current to where it was located by subtracting the length of pattern.
    current -= strlen(pattern);

    return reinterpret_cast<T*>(*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(current) + offset));
}