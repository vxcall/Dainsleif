#include "Hooks.h"
#include <stdexcept>
#include <MinHook.h>
#include "ControlCursor.h"
#include "GraphicHook.h"
#include "../Interfaces/CInterfaceList.h"
#include "../Utils.h"

namespace Hooks
{
    void Initialize()
    {
        if (MH_Initialize() != MH_OK)
        {
            throw std::runtime_error("Failed to initialize minhook!");
        }

        InitializeGraphicHook();
        HookLockCursor();

        if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
        {
            throw std::runtime_error("Failed to enable hooks!");
        }
    }

    void Restore()
    {
        if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK)
        {
            throw std::runtime_error("Failed to disable hooks!");
        }

        ShutDownGraphicHook();

        if (MH_Uninitialize() != MH_OK)
        {
            throw std::runtime_error("Failed to uninitialize minhook!");
        }
    }
}