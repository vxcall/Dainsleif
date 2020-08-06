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
#include <detours.h>

//my header
#include "Hook/ImGuiTheme.h"
#include "vector3.h"
#include "DefaultSettings.h"
#include "offsets.h"
#include "Modules.h"
#include "Utils.h"

//external library
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "toml.hpp"


#endif
