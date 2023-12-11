cmake_minimum_required(VERSION 3.16)
project(AL-dist)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_TEST "Buduje testy jednostkowe" ON)

add_subdirectory("third party/SDL")
add_subdirectory(src)

if (BUILD_TEST)
    add_subdirectory("third party/googletest")
    add_subdirectory(test)
endif()