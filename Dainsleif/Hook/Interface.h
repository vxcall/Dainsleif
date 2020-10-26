#pragma once
#include "../pch.h"

// function prototype for CreateInterface that is reversed by someone else.
using tCreateInterface = void* (*) ( const char*, int* );

namespace Interface {
    tCreateInterface GetCreateInterface(HMODULE mod);

    //GetInterface returns the result of CreateInterface.
    template<class t>
    t* GetInterface(tCreateInterface CreateInterface, const std::string &interfaceVersion) {
        auto result = static_cast<t*>(CreateInterface(interfaceVersion.data(), nullptr));
        return result;
    }
}