cmake_minimum_required(VERSION 3.16)
project(HACK4CSGO)

set(CMAKE_CXX_STANDARD 17)

#Directx9
include_directories($ENV{DXSDK_DIR}/Include)
link_directories($ENV{DXSDK_DIR}/Lib/x86)

#MSDetour
include_directories(${CMAKE_SOURCE_DIR}/Dependencies/MSDetour/include)
link_directories(${CMAKE_SOURCE_DIR}/Dependencies/MSDetour/binary)

#imGUI
include_directories(${CMAKE_SOURCE_DIR}/Dependencies/imGUI)
set(IMGUI_FILE_PATH ${CMAKE_SOURCE_DIR}/Dependencies/imGUI)
set(IMGUI_FILES ${IMGUI_FILE_PATH}/imconfig.h ${IMGUI_FILE_PATH}/imgui.cpp ${IMGUI_FILE_PATH}/imgui.h ${IMGUI_FILE_PATH}/imgui_demo.cpp ${IMGUI_FILE_PATH}/imgui_draw.cpp ${IMGUI_FILE_PATH}/imgui_impl_dx9.cpp ${IMGUI_FILE_PATH}/imgui_impl_dx9.h ${IMGUI_FILE_PATH}/imgui_impl_win32.cpp ${IMGUI_FILE_PATH}/imgui_impl_win32.h ${IMGUI_FILE_PATH}/imgui_internal.h ${IMGUI_FILE_PATH}/imgui_widgets.cpp ${IMGUI_FILE_PATH}/imstb_rectpack.h ${IMGUI_FILE_PATH}/imstb_textedit.h ${IMGUI_FILE_PATH}/imstb_truetype.h)

#toml11
include_directories(${CMAKE_SOURCE_DIR}/Dependencies/toml)

add_library(HACK4CSGO SHARED dllmain.cpp Entity.cpp Entity.h framework.h LocalPlayer.cpp LocalPlayer.h offsets.h pch.cpp pch.h vector3.cpp vector3.h ${IMGUI_FILES} GraphicHook.cpp GraphicHook.h)

target_link_libraries(${PROJECT_NAME} d3d9 detours)