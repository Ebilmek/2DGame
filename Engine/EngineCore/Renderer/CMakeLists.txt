# CMakeList.txt : CMake project for EngineCore
#
cmake_minimum_required (VERSION 3.19)

target_sources (EngineCore PRIVATE "TextureHandler.h" "TextureHandler.cpp" 
    "Renderer.h" "Renderer.cpp"
    "FontHandler.h" "FontHandler.cpp"
    "RenderableFactory.h" 
    "ImageContainer.h"
    "FontInfoHandler.h" "FontInfoHandler.cpp"
    "TextureInfoHandler.h" "TextureInfoHandler.cpp")

target_include_directories(EngineCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
