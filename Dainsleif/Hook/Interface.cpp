#include "Interface.h"

//GetCreateInterface returns a new CreateInterface function to get interface in each modules.
tCreateInterface Interface::GetCreateInterface(const HMODULE mod) {
    return reinterpret_cast<tCreateInterface>(GetProcAddress(mod, "CreateInterface"));
}