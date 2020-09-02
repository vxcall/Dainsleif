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

#MSDetour
include_directories(${CMAKE_CURRENT_LIST_DIR}/Dependencies/MSDetour/include)
link_directories(${CMAKE_CURRENT_LIST_DIR}/Dependencies/MSDetour/binary)

#imGUI
include_directories(${CMAKE_CURRENT_LIST_DIR}/Dependencies/imGUI)
FILE(GLOB_RECURSE IMGUI_SOURCE CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/Dependencies/imGUI/*.cpp)
FILE(GLOB_RECURSE IMGUI_HEADER CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/Dependencies/imGUI/*.h)

#toml11
include_directories(${CMAKE_CURRENT_LIST_DIR}/Dependencies/toml11)

#Hacks directory
FILE(GLOB_RECURSE HACKS_SOURCE CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/Dainsleif/Hacks/*.cpp)
FILE(GLOB_RECURSE HACKS_HEADER CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/Dainsleif/Hacks/*.h)

#main directory
FILE(GLOB_RECURSE MAIN_SOURCE CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/Dainsleif/*.cpp)
FILE(GLOB_RECURSE MAIN_HEADER CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/Dainsleif/*.h)

add_library(Dainsleif SHARED ${MAIN_SOURCE} ${MAIN_HEADER} ${HACKS_SOURCE} ${HACKS_HEADER} ${IMGUI_SOURCE} ${IMGUI_HEADER})

if (MSVC)
  target_link_options(${PROJECT_NAME} PRIVATE "/SAFESEH:NO")
endif ()

target_link_libraries(${PROJECT_NAME} d3d9 d3dx9 detours)