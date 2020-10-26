#include "Interface.h"

//GetCreateInterface returns a new CreateInterface function to get interface in each modules.
tCreateInterface Interface::GetCreateInterface(const HMODULE mod) {
    return reinterpret_cast<tCreateInterface>(GetProcAddress(mod, "CreateInterface"));
}

//GetInterface returns the result of CreateInterface.
template<class t>
t* Interface::GetInterface(const tCreateInterface CreateInterface, const std::string& interfaceVersion) {
    auto result = static_cast<t*>(CreateInterface(interfaceVersion.data(), nullptr));
    return result;
}