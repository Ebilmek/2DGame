project(2DGame_Test)
include(googletest)

add_executable(2DGame_Test)

# Glob the source files so I don't have to keep updating this
# Not recommended, target sources would update automatically
file(GLOB TestSrc ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
target_sources(2DGame_Test PRIVATE ${TestSrc})

find_package(SDL2 REQUIRED)

# Link gtest
target_link_libraries(2DGame_Test PRIVATE gtest_main SDL2::Main EngineCore EngineMath)

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
    TARGET 2DGame_Test POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SDL2_PATH}/lib/${Processor}/SDL2.dll" $<TARGET_FILE_DIR:2DGame_Test>
    VERBATIM
)

# SDL_image
# Loops through the missing DLLs and moves each one that's missing from destination .exe folder
file(GLOB IMAGE_DLLS ${SDL2_IMAGE_PATH}/lib/${Processor}/*.dll)
foreach(CurrentDLL IN LISTS IMAGE_DLLS)
    add_custom_command(
        TARGET 2DGame_Test POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CurrentDLL} $<TARGET_FILE_DIR:2DGame_Test>
        COMMENT "Copying DLL: ${CurrentDLL}"
        VERBATIM
    )
endforeach()

#set(DG_CREATE_SHARED_LIBRARY ON)
#set(DGTEST_LINKED_AS_SHARED_LIBRARY ON)

gtest_discover_tests(2DGame_Test)