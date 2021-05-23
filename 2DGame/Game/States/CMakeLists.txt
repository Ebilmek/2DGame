# CMakeList.txt : CMake project for 2DGame
#
cmake_minimum_required (VERSION 3.19)

target_sources (2DGame PRIVATE "StateBase.h" "StateList.h" 
    "MainMenuState.h" "MainMenuState.cpp"
    "SettingsState.h" "SettingsState.cpp"
    "GameState.h" "GameState.cpp"
    "StateHandler.h" "StateHandler.cpp"
    "StateMain.h")

target_include_directories(2DGame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})