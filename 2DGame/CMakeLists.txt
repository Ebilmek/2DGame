# CMakeList.txt : CMake project for 2DGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.19)

# Add source to this project's executable.
add_executable (2DGame WIN32)

target_sources (2DGame PRIVATE "2DGame.cpp" "2DGame.h")

find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)

target_link_libraries(2DGame PRIVATE SDL2::Main EngineCore EngineMath)

#Include subdirectories
add_subdirectory ("Game")

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
    TARGET 2DGame POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SDL2_PATH}/lib/${Processor}/SDL2.dll" $<TARGET_FILE_DIR:2DGame>
)

# SDL_image
# Loops through the missing DLLs and moves each one that's missing from destination .exe folder
file(GLOB IMAGE_DLLS ${SDL2_IMAGE_PATH}/lib/${Processor}/*.dll)
foreach(CurrentDLL IN LISTS IMAGE_DLLS)
    add_custom_command(
        TARGET 2DGame POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CurrentDLL} $<TARGET_FILE_DIR:2DGame>
        COMMENT "Copying DLL: ${CurrentDLL}"
    )
endforeach()

# Personal note: having /.. after current source would 
target_include_directories(2DGame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})