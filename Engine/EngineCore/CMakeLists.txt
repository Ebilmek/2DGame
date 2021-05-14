# CMakeList.txt : CMake project for Engine Core
#
cmake_minimum_required (VERSION 3.19)

add_library(EngineCore STATIC)
#set_property(TARGET EngineCore PROPERTY CXX_STANDARD 20)
# Only for this so doesn't affect other libraries or projects?
target_compile_features(EngineCore PRIVATE cxx_std_20)

# Personal note: can put this inside add_library above, but it's cleaner split
target_sources (EngineCore PRIVATE 
    "SHDebug.cpp" "SHDebug.h"
    "Input.cpp" "Input.h"
    "WindowSDL.cpp" "WindowSDL.h" 
    "Sprite.h" "Sprite.cpp" 
    "TextureHandler.h" "TextureHandler.cpp" 
    "Renderer.h" "Renderer.cpp" 
    "ImageContainer.h" 
    "Renderable.h" 
    "TextRenderable.h" 
    "Font.h" 
    "AnimatedSprite.h" "AnimatedSprite.cpp" 
    "EventFacade.h" "EventFacade.cpp" 
    "FontHandler.h" "FontHandler.cpp")

add_subdirectory("Events")
add_subdirectory("RenderableInfo")

# Personal note: Looks at size of a pointer on current system
# Looked into other means of doing this but most have been deprecated
# as of 3.20 this is still in use
if(CMAKE_SIZEOF_VOID_P EQUAL 8) # x64
    set(Processor "x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)  # x86
    set(Processor "x86")
else() # Not supported
    message( FATAL_ERROR "Toaster/super computer detected, not a 64/32bit processor")
endif()

#Move the SDL DLLs into position
#TODO: expand for use with x86 and make it simpler for implementing other libraries (i.e. gfx/image)
#TODO: look for a way to do this within engine core, as majority of these will be used within that,
#       however, the EngineCore doesn't have the location of the .exe directory (at least no easy way to find it)
add_custom_command(
    TARGET EngineCore POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SDL2_PATH}/lib/${Processor}/SDL2.dll" $<TARGET_FILE_DIR:2DGame>
    VERBATIM
)

# SDL_image
# Loops through the missing DLLs and moves each one that's missing from destination .exe folder
file(GLOB IMAGE_DLLS ${SDL2_IMAGE_PATH}/lib/${Processor}/*.dll)
foreach(CurrentDLL IN LISTS IMAGE_DLLS)
    add_custom_command(
        TARGET EngineCore POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CurrentDLL} $<TARGET_FILE_DIR:2DGame>
        COMMENT "Copying IMG DLL: ${CurrentDLL}"
        VERBATIM
    )
endforeach()

# SDL_ttf
# Loops through the missing DLLs and moves each one that's missing from destination .exe folder
file(GLOB IMAGE_DLLS ${SDL2_TTF_PATH}/lib/${Processor}/*.dll)
foreach(CurrentDLL IN LISTS IMAGE_DLLS)
    add_custom_command(
        TARGET EngineCore POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CurrentDLL} $<TARGET_FILE_DIR:2DGame>
        COMMENT "Copying TTF DLL: ${CurrentDLL}"
        VERBATIM
    )
endforeach()

# Personal note: having /.. after current source would 
target_include_directories(EngineCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} PRIVATE ${SDL2_TTF_INCLUDE_DIR})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(EngineCore PRIVATE SDL2::Core SDL2::Image SDL2::TTF EngineMath)
