//
// Created by Elias Aggergaard Larsen on 26/09/2024.
//

#ifndef BOARD_H
#define BOARD_H
#include <cstdint>


class Board
{
public:
    Board();
    Board(Board& board);

private:
    uint64_t wPawns_;
    uint64_t wRooks;
    uint64_t wKnights;
    uint64_t wBishops;
    uint64_t wQueens;
    uint64_t wKing;
    uint64_t bPawns;
    uint64_t bRooks;
    uint64_t bKnights;
    uint64_t bBishops;
    uint64_t bQueens;
    uint64_t bKing;
};


#endif //BOARD_H
