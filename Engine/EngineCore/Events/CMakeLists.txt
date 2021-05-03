# CMakeList.txt : CMake project for EngineCore
#
cmake_minimum_required (VERSION 3.19)

target_sources (EngineCore PRIVATE "ReverseSubject.h" "ReverseSubject.cpp"
                "ReverseObserver.h" "ReverseObserver.cpp"
                "Event.h")