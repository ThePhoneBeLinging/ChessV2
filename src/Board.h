//
// Created by Elias Aggergaard Larsen on 26/09/2024.
//

#ifndef BOARD_H
#define BOARD_H
#include <cstdint>
#include <vector>
#include "MoveGeneration.h"
#include "Move.h"


class Board
{
public:
    Board();
    Board(Board& board);
    std::vector<Move> generateAllLegalMoves(bool isWhite);

private:
    bool isMoveLegal(const Move& move, bool isWhite);
    uint64_t whitePawnsBitBoard_;
    uint64_t whiteRooksBitBoard_;
    uint64_t whiteKnightsBitBoard_;
    uint64_t whiteBishopsBitBoard_;
    uint64_t whiteQueensBitBoard_;
    uint64_t whiteKingBitBoard_;
    uint64_t blackPawnsBitBoard_;
    uint64_t blackRooksBitBoard_;
    uint64_t blackKnightsBitBoard_;
    uint64_t blackBishopsBitBoard_;
    uint64_t blackQueensBitBoard_;
    uint64_t blackKingBitBoard_;
};


#endif //BOARD_H
