#include "PatternScanner.h"
#include <Windows.h>
#include "Modules.h"
#include <Psapi.h>
#include <string>

//expect value like this -> \x0F\x11\x05????\x83\xC8\x01
uintptr_t PatternScanner::FindPattern(const char* pattern) {
    static auto id = 0;
    ++id;

    if (HMODULE moduleHandle = GetModuleHandleA("client.dll")) {
        if (MODULEINFO moduleInfo; GetModuleInformation(GetCurrentProcess(), moduleHandle, &moduleInfo, sizeof(moduleInfo))) {
            auto start = static_cast<const char*>(moduleInfo.lpBaseOfDll);
            const auto end = start + moduleInfo.SizeOfImage;

            auto first = start;
            auto second = pattern;

            while (first < end && *second) {
                if (*first == *second || *second == '?') {
                    ++first;
                    ++second;
                } else {
                    first = ++start;
                    second = pattern;
                }
            }

            if (!*second)
                return reinterpret_cast<std::uintptr_t>(start);
        }
    }
    MessageBoxA(NULL, ("Failed to find pattern #" + std::to_string(id) + '!').c_str(), "Osiris", MB_OK | MB_ICONWARNING);
    return 0;
}