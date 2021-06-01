cmake_minimum_required(VERSION 3.16)
project(Dainsleif)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_GENERATOR MATCHES "Visual Studio")
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  file(GLOB_RECURSE SOURCE_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c *.cpp *.h *.hpp)
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST})
endif ()

#Directx9
include_directories($ENV{DXSDK_DIR}/Include)
link_directories($ENV{DXSDK_DIR}/Lib/x86)

#minhook
include_directories(${CMAKE_CURRENT_LIST_DIR}/Dependencies/minhook/include)
file(GLOB_RECURSE MINHOOK CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_LIST_DIR}/Dependencies/minhook/*.c
  ${CMAKE_CURRENT_LIST_DIR}/Dependencies/minhook/*.h)

#imGUI
include_directories(${CMAKE_CURRENT_LIST_DIR}/Dependencies/imGUI)
file(GLOB_RECURSE IMGUI CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_LIST_DIR}/Dependencies/imGUI/*.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Dependencies/imGUI/*.h)

#toml11
include_directories(${CMAKE_CURRENT_LIST_DIR}/Dependencies/toml11)
file(GLOB_RECURSE TOML CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/Dependencies/toml11/*.hpp)

#main directory and its sub-directories
file(GLOB_RECURSE MAIN CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_LIST_DIR}/Dainsleif/*.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Dainsleif/*.h)

add_library(Dainsleif SHARED ${MAIN} ${MINHOOK} ${IMGUI} ${TOML})

target_link_libraries(${PROJECT_NAME} d3d9 d3dx9)