#include "../Dainsleif/Interfaces/CInterfaceList.h"

CInterfaceList g_csgo;

void CInterfaceList::Initialize ( )
{
    const fnCreateInterface engineFactory = GetModuleFactory ( GetModuleHandleA ( "engine.dll" ) );
    const fnCreateInterface surfaceFactory = GetModuleFactory ( GetModuleHandleA ( "vguimatsurface.dll" ) );

    engine = GetInterface< IVEngineClient > ( engineFactory, "VEngineClient014" );
    surface = GetInterface< ISurface > ( surfaceFactory, "VGUI_Surface031" );

#if _DEBUG
    PrintInterfaces ( );
#endif
}
