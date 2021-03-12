# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.19)

project ("2DGame" LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Include sub-projects.
add_subdirectory ("SDL2")
add_subdirectory ("2DGame")
add_subdirectory ("Engine")

# Check if we have SDL2 MAIN
#if(TARGET SDL2::Main) 
#    message(STATUS "SDL2 found")
#else()
#    message(STATUS "Hello, if you're seeing this: scream")
#endif()