# CMakeList.txt : CMake project for 2DGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.19)

# Add source to this project's executable.
add_executable (2DGame)

target_sources (2DGame PRIVATE "2DGame.cpp" "2DGame.h")

find_package(SDL2 REQUIRED)

target_link_libraries(2DGame SDL2::Main)

#TODO: expand for use with x86 and make it simpler for implementing other libraries (i.e. gfx/image)
add_custom_command(
    TARGET 2DGame POST_BUILD 
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_PROPERTY:SDL2::Main,IMPORTED_LOCATION> $<TARGET_FILE_DIR:2DGame>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SDL2_PATH}/lib/x64/SDL2.dll" $<TARGET_FILE_DIR:2DGame>
)