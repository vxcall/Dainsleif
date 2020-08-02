cmake_minimum_required(VERSION 3.16)
project(Dainsleif)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_GENERATOR MATCHES "Visual Studio")
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  source_group(Dependencies REGULAR_EXPRESSION ${CMAKE_CURRENT_LIST_DIR}/Dependencies/*)
endif ()

#Directx9
include_directories($ENV{DXSDK_DIR}/Include)
link_directories($ENV{DXSDK_DIR}/Lib/x86)

#MSDetour
include_directories(${CMAKE_CURRENT_LIST_DIR}/Dependencies/MSDetour/include)
link_directories(${CMAKE_CURRENT_LIST_DIR}/Dependencies/MSDetour/binary)

#imGUI
include_directories(${CMAKE_CURRENT_LIST_DIR}/Dependencies/imGUI)
set(IMGUI_FILE_PATH ${CMAKE_CURRENT_LIST_DIR}/Dependencies/imGUI)
set(IMGUI_FILES ${IMGUI_FILE_PATH}/imconfig.h ${IMGUI_FILE_PATH}/imgui.cpp ${IMGUI_FILE_PATH}/imgui.h ${IMGUI_FILE_PATH}/imgui_demo.cpp
        ${IMGUI_FILE_PATH}/imgui_draw.cpp ${IMGUI_FILE_PATH}/imgui_impl_dx9.cpp ${IMGUI_FILE_PATH}/imgui_impl_dx9.h
        ${IMGUI_FILE_PATH}/imgui_impl_win32.cpp ${IMGUI_FILE_PATH}/imgui_impl_win32.h ${IMGUI_FILE_PATH}/imgui_internal.h
        ${IMGUI_FILE_PATH}/imgui_widgets.cpp ${IMGUI_FILE_PATH}/imstb_rectpack.h ${IMGUI_FILE_PATH}/imstb_textedit.h ${IMGUI_FILE_PATH}/imstb_truetype.h)

#toml11
include_directories(${CMAKE_CURRENT_LIST_DIR}/Dependencies/toml11)

#Hacks directory
set(HACKS_FILES Dainsleif/Hacks/Aimbot.cpp Dainsleif/Hacks/Aimbot.h Dainsleif/Hacks/Glow.cpp Dainsleif/Hacks/Glow.h Dainsleif/Hacks/AntiRecoil.cpp Dainsleif/Hacks/AntiRecoil.h Dainsleif/Hacks/Triggerbot.cpp Dainsleif/Hacks/Triggerbot.h)

add_library(Dainsleif SHARED Dainsleif/dllmain.cpp Dainsleif/Entity.cpp Dainsleif/Entity.h Dainsleif/LocalPlayer.cpp Dainsleif/LocalPlayer.h Dainsleif/offsets.h Dainsleif/pch.cpp Dainsleif/pch.h Dainsleif/vector3.cpp Dainsleif/vector3.h Dainsleif/Hook/GraphicHook.cpp Dainsleif/Hook/GraphicHook.h Dainsleif/Hook/ImGuiTheme.cpp Dainsleif/Hook/ImGuiTheme.h ${IMGUI_FILES} ${HACKS_FILES} Dainsleif/RWtoml.cpp Dainsleif/RWtoml.h)

if (MSVC)
  target_link_options(${PROJECT_NAME} PRIVATE "/SAFESEH:NO")
endif (MSVC)

target_link_libraries(${PROJECT_NAME} d3d9 detours)