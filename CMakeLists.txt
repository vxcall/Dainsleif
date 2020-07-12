cmake_minimum_required(VERSION 3.16)
project(HACK4CSGO)

set(CMAKE_CXX_STANDARD 20)

add_library(HACK4CSGO SHARED dllmain.cpp Entity.cpp Entity.h framework.h LocalPlayer.cpp LocalPlayer.h offsets.h pch.cpp pch.h vector3.cpp vector3.h)
