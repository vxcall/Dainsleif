#include "Modules.h"
#include <Windows.h>

namespace Modules
{
    uintptr_t client;
    uintptr_t engine;

    void Initialize()
    {
        client = reinterpret_cast<uintptr_t>(GetModuleHandle("client.dll"));
        engine = reinterpret_cast<uintptr_t>(GetModuleHandle("engine.dll"));
    }
}