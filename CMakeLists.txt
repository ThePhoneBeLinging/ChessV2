cmake_minimum_required(VERSION 3.28)
project(ChessV2)

set(CMAKE_BUILD_FLAGS "-Wall -Wextra -Wpedantic -Werror")
set(CMAKE_CXX_STANDARD 20)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resources
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(GTest REQUIRED)


add_subdirectory(src)

add_subdirectory(dependencies/Utility)
add_subdirectory(dependencies/EngineBase)

enable_testing()