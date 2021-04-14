# CMakeList.txt : CMake project for Engine Core
#
cmake_minimum_required (VERSION 3.19)

add_library(EngineCore STATIC)
#set_property(TARGET EngineCore PROPERTY CXX_STANDARD 20)
# Only for this so doesn't affect other libraries or projects?
target_compile_features(EngineCore PRIVATE cxx_std_20)

# Personal note: can put this inside add_library, but it's cleaner split
target_sources (EngineCore PRIVATE 
    "SHDebug.cpp" "SHDebug.h"
    "Input.cpp" "Input.h"
    "WindowSDL.cpp" "WindowSDL.h" 
    "Sprite.h" "Sprite.cpp" 
    "TextureHandler.h" "TextureHandler.cpp" 
    "SpriteInfo.h" 
    "Renderer.h" "Renderer.cpp" 
    "ImageContainer.h" 
    "Renderable.h")

# Personal note: having /.. after current source would 
target_include_directories(EngineCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_link_libraries(EngineCore PRIVATE SDL2::Core SDL2::Image EngineMath)
