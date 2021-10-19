#include "CInterfaceList.h"

CInterfaceList g_csgo;

void CInterfaceList::Initialize ( )
{
    const fnCreateInterface clientFactory = GetModuleFactory(GetModuleHandleA("client.dll"));
    const fnCreateInterface engineFactory = GetModuleFactory ( GetModuleHandleA ( "engine.dll" ) );
    const fnCreateInterface surfaceFactory = GetModuleFactory ( GetModuleHandleA ( "vguimatsurface.dll" ) );

    client = GetInterface<IBaseClientDll>(clientFactory, "VClient018");
    clientMode = **reinterpret_cast<IClientModeShared***>(Utils::GetVirtualFunction<std::uintptr_t>(client, 10) + 0x5); //CHLClient::HudProcessInput + 0x5
    engine = GetInterface< IVEngineClient > ( engineFactory, "VEngineClient014" );
    surface = GetInterface< ISurface > ( surfaceFactory, "VGUI_Surface031" );

#if _DEBUG
    PrintInterfaces ( );
#endif
}
