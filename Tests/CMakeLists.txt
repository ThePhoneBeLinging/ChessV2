cmake_minimum_required(VERSION 3.28)
project(ChessV2_Tests)

set(CMAKE_CXX_STANDARD 23)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
set(SOURCES
        ../src/Board.cpp
        BoardTest.cpp
        # Add other source files here
)
add_executable(ChessV2_Tests ${SOURCES})

target_link_libraries(ChessV2_Tests PUBLIC
        GTest::GTest
        GTest::Main
        EngineBase
)