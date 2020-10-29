#pragma once

#include "../Interfaces/ISurface.h"

using tLockCursor = void(__thiscall*) ( ISurface* );

void HookLockCursor ( );
