#CMakeList.txt : CMake project for EngineCore
#
cmake_minimum_required (VERSION 3.19)

target_sources (EngineCore PRIVATE "Renderable.h" 
    "TextRenderable.h" 
    "AnimatedSprite.h" "AnimatedSprite.cpp" 
     "Sprite.h" "Sprite.cpp")

target_include_directories(EngineCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
