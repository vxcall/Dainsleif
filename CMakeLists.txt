cmake_minimum_required(VERSION 3.16)
project(Dainsleif)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_GENERATOR MATCHES "Visual Studio")
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  file(GLOB_RECURSE SOURCE_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS *.c *.cpp *.h *.hpp)
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST})
endif()

#main directory and its sub-directories
file(GLOB_RECURSE MAIN CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_LIST_DIR}/Dainsleif/*.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Dainsleif/*.h)

#minhook
file(GLOB_RECURSE MINHOOK CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_LIST_DIR}/Dependencies/minhook/*.c
  ${CMAKE_CURRENT_LIST_DIR}/Dependencies/minhook/*.h)

#imgui
file(GLOB IMGUI CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_LIST_DIR}/Dependencies/imgui/*.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Dependencies/imgui/*.h
  ${CMAKE_CURRENT_LIST_DIR}/Dependencies/imgui/backends/imgui_impl_dx9.*
  ${CMAKE_CURRENT_LIST_DIR}/Dependencies/imgui/backends/imgui_impl_win32.*)

#toml11
file(GLOB_RECURSE TOML CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_LIST_DIR}/Dependencies/toml11/*.hpp)

set(DEPENDENCIES
  ${MINHOOK}
  ${IMGUI}
  ${TOML})

add_library(Dainsleif SHARED ${MAIN} ${DEPENDENCIES})

target_include_directories(Dainsleif PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/Dependencies/imgui
  ${CMAKE_CURRENT_LIST_DIR}/Dependencies/imgui/backends
  ${CMAKE_CURRENT_LIST_DIR}/Dependencies/minhook/include
  ${CMAKE_CURRENT_LIST_DIR}/Dependencies/toml11
  $ENV{DXSDK_DIR}/Include)

find_library(D3D9 d3d9.lib $ENV{DXSDK_DIR}/Lib/x86)
find_library(D3DX9 d3dx9.lib $ENV{DXSDK_DIR}/Lib/x86)
target_link_libraries(Dainsleif ${D3D9} ${D3DX9})