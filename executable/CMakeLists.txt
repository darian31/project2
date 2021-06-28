cmake_minimum_required(VERSION 3.10.0)
project(NOVELL CXX)
include(${CMAKE_CURRENT_LIST_DIR}/../cmake/Tester.cmake)
auto_tester(novell lib.cpp novelist_test.cpp)
add_executable(novellReader main.cpp)
add_executable(novelist novelist.cpp lib.cpp)

