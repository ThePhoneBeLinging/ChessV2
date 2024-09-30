cmake_minimum_required(VERSION 3.28)
project(ChessV2)

set(CMAKE_BUILD_FLAGS "-Wall -Wextra -Wpedantic -Werror")
set(CMAKE_CXX_STANDARD 23)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resources
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1  # Specify the version you need
)

FetchContent_MakeAvailable(googletest)


add_subdirectory(dependencies/Utility)
add_subdirectory(dependencies/EngineBase)
add_subdirectory(Tests)
add_subdirectory(src)
enable_testing()