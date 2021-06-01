#ifndef PCH_H
#define PCH_H

//standard library
#include <fstream>
#include <direct.h>
#include <sys/stat.h>
#include <iostream>
#include <shlobj.h>
#include <vector>
#include <filesystem>
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9core.h>


//my header
#include "Hook/ImGuiTheme.h"
#include "Vector.h"
#include "DefaultSettings.h"
#include "Offsets.h"
#include "Modules.h"
#include "Utils.h"

//external library
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "toml.hpp"


#endif
