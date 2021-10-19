#include "Hooks.h"
#include <stdexcept>
#include <MinHook.h>
#include "ControlCursor.h"
#include "GraphicHook.h"
#include "../Interfaces/CInterfaceList.h"
#include "../Utils.h"
#include "../Player.h"

extern int fov; //declared in dllmain.cpp

namespace Hooks
{
    using FnOverrideView = void (__thiscall*)(IClientModeShared* clientMode, ViewSetup* setup);
    FnOverrideView originalOverrideView = nullptr;

    void __fastcall HookedOverrideView(IClientModeShared* clientMode, int edx, ViewSetup* setup)
    {
        Player* localPlayer = Player::GetLocalPlayer();
        if (!localPlayer || localPlayer->isScoped()) {
            originalOverrideView(clientMode, setup);
            return;
        }

        setup->m_flFOV = fov;
        originalOverrideView(clientMode, setup);
    }

    void Initialize()
    {
        if (MH_Initialize() != MH_OK)
        {
            throw std::runtime_error("Failed to initialize minhook!");
        }

        InitializeGraphicHook();
        HookLockCursor();

        void* overrideView = Utils::GetVirtualFunction<void*>(g_csgo.clientMode, 18);
        if (MH_CreateHookEx(overrideView, &HookedOverrideView, &originalOverrideView) != MH_OK)
        {
            throw std::runtime_error("Failed to hook OverrideView!");
        }

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