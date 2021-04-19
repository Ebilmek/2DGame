# CMakeList.txt : CMake project for 2DGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.19)

# FINDSDL2 sorts subfolders
set(SDL2_TTF_PATH "${CMAKE_CURRENT_SOURCE_DIR}" CACHE STRING "Root folder for SDL2_ttf library" FORCE)