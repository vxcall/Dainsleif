cmake_minimum_required(VERSION 3.16)
project(HACK4CSGO)

set(CMAKE_CXX_STANDARD 20)

#Directx9
include_directories($ENV{DXSDK_DIR}/Include)
link_directories($ENV{DXSDK_DIR}/Lib/x86)

#MSDetour
include_directories(${CMAKE_SOURCE_DIR}/Dependencies/MSDetour/include)
link_directories(${CMAKE_SOURCE_DIR}/Dependencies/MSDetour/bin)

#imGUI
set(IMGUI_FILES ${CMAKE_SOURCE_DIR}/Dependencies/imGUI)
include_directories(${IMGUI_FILES})


set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_library(HACK4CSGO SHARED dllmain.cpp Entity.cpp Entity.h framework.h LocalPlayer.cpp LocalPlayer.h offsets.h pch.cpp pch.h vector3.cpp vector3.h ${IMGUI_FILES}/imconfig.h ${IMGUI_FILES}/imgui.cpp ${IMGUI_FILES}/imgui.h ${IMGUI_FILES}/imgui_demo.cpp ${IMGUI_FILES}/imgui_draw.cpp ${IMGUI_FILES}/imgui_impl_dx9.cpp ${IMGUI_FILES}/imgui_impl_dx9.h ${IMGUI_FILES}/imgui_impl_win32.cpp ${IMGUI_FILES}/imgui_impl_win32.h ${IMGUI_FILES}/imgui_internal.h ${IMGUI_FILES}/imgui_widgets.cpp ${IMGUI_FILES}/imstb_rectpack.h ${IMGUI_FILES}/imstb_textedit.h ${IMGUI_FILES}/imstb_truetype.h)

target_link_libraries(${PROJECT_NAME} d3d9 d3dx9 detours)