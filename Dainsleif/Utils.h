#pragma once
#include <cstddef>

namespace Utils
{
    template <typename T>
    T GetVFunc(void* object, std::size_t index)
    {
        void** vTable = *reinterpret_cast<void***>(object);
        void* vFunc = vTable[index];
        return reinterpret_cast<T>(vFunc);
    }

    template <typename T, typename... Args>
    T CallVFunc(void* object, std::size_t index, Args... args)
    {
        return GetVFunc<T(__thiscall*)(void*, Args...)>(object, index)(object, args...);
    }
}