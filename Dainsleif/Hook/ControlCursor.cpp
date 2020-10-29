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
    void** vTable = *reinterpret_cast< void*** > ( g_csgo.surface );
    oLockCursor = reinterpret_cast< tLockCursor > ( DetourFunction ( static_cast< PBYTE > ( vTable[ 67 ] ), reinterpret_cast< PBYTE > ( hLockCursor ) ) );
}
