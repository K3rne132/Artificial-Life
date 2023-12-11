cmake_minimum_required(VERSION 3.16)
project(ArtificialLife)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES
    "*.h"
    "*.hpp"
    "*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})
add_library(lib${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(lib${PROJECT_NAME} INTERFACE /)
target_link_libraries(${PROJECT_NAME} SDL2)
target_link_libraries(lib${PROJECT_NAME} SDL2)