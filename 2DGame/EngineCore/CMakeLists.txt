# CMakeList.txt : CMake project for 2DGame
#
cmake_minimum_required (VERSION 3.19)

target_sources (2DGame PRIVATE "WindowSDL.cpp" "WindowSDL.h"
    "Input.cpp" "Input.h")