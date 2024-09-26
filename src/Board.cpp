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
    whitePawnsBitBoard_ = 0x000000000000FF00;
    whiteRooksBitBoard_ = 0x0000000000000081;
    whiteKnightsBitBoard_ = 0x0000000000000042;
    whiteBishopsBitBoard_ = 0x0000000000000024;
    whiteQueensBitBoard_ = 0x0000000000000010;
    whiteKingBitBoard_ = 0x0000000000000008;

    // Initialize black pieces
    blackPawnsBitBoard_ = 0x00FF000000000000;
    blackRooksBitBoard_ = 0x8100000000000000;
    blackKnightsBitBoard_ = 0x4200000000000000;
    blackBishopsBitBoard_ = 0x2400000000000000;
    blackQueensBitBoard_ = 0x1000000000000000;
    blackKingBitBoard_ = 0x0800000000000000;

    // Debug print the initial positions
    std::cout << "White Pawns:\n";
    DebugPrints::printMatrix(whitePawnsBitBoard_);
    std::cout << "White Rooks:\n";
    DebugPrints::printMatrix(whiteRooksBitBoard_);
    std::cout << "White Knights:\n";
    DebugPrints::printMatrix(whiteKnightsBitBoard_);
    std::cout << "White Bishops:\n";
    DebugPrints::printMatrix(whiteBishopsBitBoard_);
    std::cout << "White Queens:\n";
    DebugPrints::printMatrix(whiteQueensBitBoard_);
    std::cout << "White King:\n";
    DebugPrints::printMatrix(whiteKingBitBoard_);
    std::cout << "Black Pawns:\n";
    DebugPrints::printMatrix(blackPawnsBitBoard_);
    std::cout << "Black Rooks:\n";
    DebugPrints::printMatrix(blackRooksBitBoard_);
    std::cout << "Black Knights:\n";
    DebugPrints::printMatrix(blackKnightsBitBoard_);
    std::cout << "Black Bishops:\n";
    DebugPrints::printMatrix(blackPawnsBitBoard_);
    std::cout << "Black Queens:\n";
    DebugPrints::printMatrix(blackQueensBitBoard_);
    std::cout << "Black King:\n";
    DebugPrints::printMatrix(blackKingBitBoard_);
}


std::vector<Move> Board::generateAllLegalMoves(bool isWhite)
{
    std::vector<Move> allMoves;
    std::vector<Move> pseudoLegalMoves;

    pseudoLegalMoves = MoveGeneration::generatePawnMoves(*this, isWhite);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = MoveGeneration::generateRookMoves(*this, isWhite);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = MoveGeneration::generateKnightMoves(*this, isWhite);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = MoveGeneration::generateBishopMoves(*this, isWhite);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = MoveGeneration::generateQueenMoves(*this, isWhite);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = MoveGeneration::generateKingMoves(*this, isWhite);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    // Filter out illegal moves
    std::vector<Move> legalMoves;
    for (const Move& move : allMoves)
    {
        if (isMoveLegal(move, isWhite))
        {
            legalMoves.push_back(move);
        }
    }

    return legalMoves;
}

bool Board::isMoveLegal(const Move& move, bool isWhite)
{
    // TODO Implement logic to check if a move is legal (e.g., does not leave the king in check)
    return true;
}
