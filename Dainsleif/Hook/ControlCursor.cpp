#include "ControlCursor.h"

template<typename T>
T GetVirtualFunction(void* baseClass, const int index)
{
    return (*static_cast<T**>(baseClass))[index];
}

ISurface* surface;
CInput* input;
tLockCursor oLockCursor;

void __fastcall hLockCursor(ISurface* thisptr, void* edx)
{
    if (g_ShowMenu) {
        surface->UnlockCursor();
        input->ResetInputState();
        return;
    }
    oLockCursor(thisptr);
}

void HookLockCursor() {
    tCreateInterface ci = Interface::GetCreateInterface(GetModuleHandleA("vguimatsurface.dll"));
    surface = Interface::GetInterface<ISurface>(ci, "VGUI_Surface031");

    input = **reinterpret_cast<CInput***>(PatternScanner("client.dll", "\xB9????\xF3\x0F\x11\x04\x24\xFF\x50\x10", 1).CalculateOffset(Modules::client, 0));

    void** vTable = *reinterpret_cast<void***>(surface);
    oLockCursor = reinterpret_cast<tLockCursor>(DetourFunction(reinterpret_cast<PBYTE>(vTable[67]), reinterpret_cast<PBYTE>(hLockCursor)));
}