cmake_minimum_required(VERSION 3.28)
project(ChessV2_Tests)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES
        ../src/Board.cpp
        ../src/DepthSearch.cpp
        BoardTest.cpp
        # Add other source files here
)
add_executable(ChessV2_Tests ${SOURCES})

target_link_libraries(ChessV2_Tests PUBLIC
        GTest::gtest
        GTest::gtest_main
        EngineBase
)