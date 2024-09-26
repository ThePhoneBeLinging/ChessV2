cmake_minimum_required(VERSION 3.28)
project(ChessV2)

set(CMAKE_CXX_STANDARD 23)

add_executable(ChessV2 main.cpp
        ChessV2.cpp
        ChessV2.h
        Board.cpp
        Board.h
        DebugPrints.cpp
        DebugPrints.h
        Move.h
        MoveGeneration.cpp
        MoveGeneration.h
        Pieces.h
)

target_link_libraries(ChessV2 PUBLIC
        EngineBase
        Utility
)