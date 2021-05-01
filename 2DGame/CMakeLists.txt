# CMakeList.txt : CMake project for 2DGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.19)

# Add source to this project's executable.
add_executable (2DGame WIN32)
#set_property(TARGET 2DGame PROPERTY CXX_STANDARD 20)
# Propagates this upwards to encompass the project
target_compile_features(2DGame PUBLIC cxx_std_20)

target_sources (2DGame PRIVATE "2DGame.cpp" "2DGame.h" "Game/States/StateBase.h" "Game/States/MainMenuState.h" "Game/States/SettingsState.h" "Game/States/SettingsState.cpp" "Game/States/GameState.h")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
#find_package(SDL2_image REQUIRED)

target_link_libraries(2DGame PRIVATE SDL2::Main SDL2::TTF EngineCore EngineMath)

#Include subdirectories
add_subdirectory ("Game")

# Assets
#add_custom_target(copy_assets
#    COMMAND ${CMAKE_COMMAND} -P copy_if_different ${CMAKE_CURRENT_LIST_DIR}/copy-resources.cmake
#)
#add_dependencies(2DGame copy_assets)
#[[foreach(CurrentAsset IN LISTS project_asset_files)
    add_custom_target(copy_assets
        #TARGET 2DGame POST_BUILD
        #MAIN_DEPENDENCY 2DGame
        COMMAND ${CMAKE_COMMAND} -P copy_if_different ${CurrentAsset} $<TARGET_FILE_DIR:2DGame>/Assets
        COMMENT "Copying Asset: ${CurrentAsset}"
        VERBATIM
    )
    add_dependencies(2DGame copy_assets)
endforeach()]]

#[[foreach(CurrentAsset IN LISTS project_asset_files
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_ASSET_FILES} $<TARGET_FILE_DIR:2DGame>
    COMMENT "Copying Asset: ${PROJECT_ASSET_FILES}"
    VERBATIM
)]]
#add_dependencies(2DGame copy_assets)

#[[add_custom_command(
    TARGET 2DGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:2DGame>/Assets"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_ASSET_FILES} "$<TARGET_FILE_DIR:2DGame>/Assets"
    COMMENT "Copying Assets"
)]]
#[[ Grabs file extensions stored in list within assets ]]
add_custom_command(
    TARGET 2DGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/copy-assets.cmake
    COMMENT "Copying Assets"
)

# Personal note: having /.. after current source would 
target_include_directories(2DGame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})