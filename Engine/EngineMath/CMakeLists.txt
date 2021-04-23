# CMakeList.txt : CMake project for Engine Math
#
cmake_minimum_required (VERSION 3.19)

add_library(EngineMath STATIC)

target_sources(EngineMath PRIVATE 
    "Transform2d.cpp" "Transform2d.h"
    "Range.h")

target_include_directories(EngineMath PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(SDL2 REQUIRED)

target_link_libraries(EngineMath PRIVATE SDL2::Core)