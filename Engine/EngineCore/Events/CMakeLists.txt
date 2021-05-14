# CMakeList.txt : CMake project for EngineCore
#
cmake_minimum_required (VERSION 3.19)

target_sources (EngineCore PRIVATE "ReverseSubject.h" "ReverseSubject.cpp"
                "ReverseObserver.h" "ReverseObserver.cpp"
                "Event.h")

target_include_directories(EngineCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})