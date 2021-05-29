# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.19)

# Clang tidy - all the checks! (second thoughts - too many checks and clutters the output log... a little too much)
# Look at CMakeSettings.json, edit it and enableClangTidyCodeAnalysis etc.
# set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

project ("2DGame" LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Include sub-projects.
add_subdirectory ("Assets")
add_subdirectory ("SDL2")
add_subdirectory ("SDL2_image")
add_subdirectory ("SDL2_ttf")
add_subdirectory ("2DGame")
add_subdirectory ("Engine")

# Glob the assets
file(GLOB asset_files "${CMAKE_CURRENT_SOURCE_DIR}/Assets/*" LIST_DIRECTORIES true )
foreach(file_path ${asset_files})
    message(${file_path})
endforeach()

option(USE_UNIT_TESTS "Build and run gtest unit testing" TRUE)
if(USE_UNIT_TESTS)
    enable_testing()
    add_subdirectory("SH_Test")
    add_subdirectory ("googletest")

    # Don't build GMock
    set(BUILD_GMOCK FALSE CACHE BOOL "" FORCE)
endif()