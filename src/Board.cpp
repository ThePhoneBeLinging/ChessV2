//
// Created by Elias Aggergaard Larsen on 26/09/2024.
//

#include "Board.h"

#include <iostream>
#include <MacTypes.h>

#include "DebugPrints.h"

Board::Board()
{
    // Initialize white pieces
    wPawns_ = 0x000000000000FF00;
    wRooks = 0x0000000000000081;
    wKnights = 0x0000000000000042;
    wBishops = 0x0000000000000024;
    wQueens = 0x0000000000000010;
    wKing = 0x0000000000000008;

    // Initialize black pieces
    bPawns = 0x00FF000000000000;
    bRooks = 0x8100000000000000;
    bKnights = 0x4200000000000000;
    bBishops = 0x2400000000000000;
    bQueens = 0x1000000000000000;
    bKing = 0x0800000000000000;

    // Debug print the initial positions
    std::cout << "White Pawns:\n";
    DebugPrints::printMatrix(wPawns_);
    std::cout << "White Rooks:\n";
    DebugPrints::printMatrix(wRooks);
    std::cout << "White Knights:\n";
    DebugPrints::printMatrix(wKnights);
    std::cout << "White Bishops:\n";
    DebugPrints::printMatrix(wBishops);
    std::cout << "White Queens:\n";
    DebugPrints::printMatrix(wQueens);
    std::cout << "White King:\n";
    DebugPrints::printMatrix(wKing);
    std::cout << "Black Pawns:\n";
    DebugPrints::printMatrix(bPawns);
    std::cout << "Black Rooks:\n";
    DebugPrints::printMatrix(bRooks);
    std::cout << "Black Knights:\n";
    DebugPrints::printMatrix(bKnights);
    std::cout << "Black Bishops:\n";
    DebugPrints::printMatrix(bBishops);
    std::cout << "Black Queens:\n";
    DebugPrints::printMatrix(bQueens);
    std::cout << "Black King:\n";
    DebugPrints::printMatrix(bKing);
}
