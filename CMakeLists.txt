cmake_minimum_required(VERSION 3.16)
project(HACK4CSGO)

set(CMAKE_CXX_STANDARD 20)

#Directx9
include_directories($ENV{DXSDK_DIR}/Include)
link_directories($ENV{DXSDK_DIR}/Lib/x86)

#Minhook
include_directories(${CMAKE_SOURCE_DIR}/Dependencies/Minhook/include)
link_directories(${CMAKE_SOURCE_DIR}/Dependencies/Minhook/bin)

#MSDetour
include_directories(${CMAKE_SOURCE_DIR}/Dependencies/MSDetour/include)
link_directories(${CMAKE_SOURCE_DIR}/Dependencies/MSDetour/bin)


set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_library(HACK4CSGO SHARED dllmain.cpp Entity.cpp Entity.h framework.h LocalPlayer.cpp LocalPlayer.h offsets.h pch.cpp pch.h vector3.cpp vector3.h)

target_link_libraries(${PROJECT_NAME} d3d9 d3dx9 MinHook.x86 detours)