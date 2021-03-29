# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.19)

project ("2DGame" LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Include sub-projects.
add_subdirectory ("SDL2")
add_subdirectory ("SDL2_image")
add_subdirectory ("2DGame")
add_subdirectory ("Engine")

option(USE_UNIT_TESTS "Build and run gtest unit testing" TRUE)
if(USE_UNIT_TESTS)
    enable_testing()
    add_subdirectory("SH_Test")
    add_subdirectory ("googletest")

    set(BUILD_GMOCK FALSE CACHE BOOL "" FORCE)
endif()