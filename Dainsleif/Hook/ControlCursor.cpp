#include "ControlCursor.h"

#include "../Interfaces/CInterfaceList.h"
#include "../dllmain.h"

tLockCursor oLockCursor;

void __fastcall hLockCursor ( ISurface* surface, uintptr_t edx )
{
    if ( g_ShowMenu )
    {
        g_csgo.surface->UnlockCursor ( );
        return;
    }
    oLockCursor ( g_csgo.surface );
}

void HookLockCursor ( )
{
    void* lockCursor = Utils::GetVirtualFunction<void*>(g_csgo.surface, 67);
    if (MH_CreateHookEx(lockCursor, &hLockCursor, &oLockCursor) != MH_OK)
    {
        throw std::runtime_error("Failed to hook LockCursor!");
    }
}
