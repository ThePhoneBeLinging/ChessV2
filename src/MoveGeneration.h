// MoveGeneration.h
#ifndef MOVEGENERATION_H
#define MOVEGENERATION_H
#include <vector>
#include "Move.h"

class Board;

class MoveGeneration
{
public:
    static std::vector<Move> generatePawnMoves(const Board& board, bool isWhite);
    static std::vector<Move> generateRookMoves(const Board& board, bool isWhite);
    static std::vector<Move> generateKnightMoves(const Board& board, bool isWhite);
    static std::vector<Move> generateBishopMoves(const Board& board, bool isWhite);
    static std::vector<Move> generateQueenMoves(const Board& board, bool isWhite);
    static std::vector<Move> generateKingMoves(const Board& board, bool isWhite);
};

#endif // MOVEGENERATION_H
