#pragma once
#include "../pch.h"

// function prototype for CreateInterface that is reversed by someone else.
using tCreateInterface = void* (*) ( const char*, int* );

namespace Interface {
    tCreateInterface GetCreateInterface(HMODULE mod);

    template<class t>
    t* GetInterface(tCreateInterface CreateInterface, const std::string &interfaceVersion);
}