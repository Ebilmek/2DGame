project(2DGame_Test)
include(googletest)

add_executable(2DGame_Test)

# Glob the source files so I don't have to keep updating this
file(GLOB TestSrc ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
target_sources(2DGame_Test PRIVATE ${TestSrc})

find_package(SDL2 REQUIRED)

# Link gtest
target_link_libraries(2DGame_Test PRIVATE gtest_main SDL2::Main EngineCore)

#set(DG_CREATE_SHARED_LIBRARY ON)
#set(DGTEST_LINKED_AS_SHARED_LIBRARY ON)

gtest_discover_tests(2DGame_Test)