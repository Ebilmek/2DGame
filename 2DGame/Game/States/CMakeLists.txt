# CMakeList.txt : CMake project for 2DGame
#
cmake_minimum_required (VERSION 3.19)

target_sources (2DGame PRIVATE "StateBase.h" "StateList.h" 
    "MainMenuState.h" "MainMenuState.cpp"
    "SettingsState.h" "SettingsState.cpp"
    "GameState.h" "GameState.cpp")