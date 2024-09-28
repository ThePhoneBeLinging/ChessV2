// MoveGeneration.h
#ifndef MOVEGENERATION_H
#define MOVEGENERATION_H
#include <vector>
#include "Move.h"

class Board;

class MoveGeneration
{
public:
    static std::vector<Move> generatePawnMoves(uint64_t sameColorPieces, uint64_t isWhitePawns);
    static std::vector<Move> generateRookMoves(uint64_t sameColorPieces, uint64_t isWhiteRooks);
    static std::vector<Move> generateKnightMoves(uint64_t sameColorPieces, uint64_t isWhiteKnights);
    static std::vector<Move> generateBishopMoves(uint64_t sameColorPieces, uint64_t isWhiteBishops);
    static std::vector<Move> generateQueenMoves(uint64_t sameColorPieces, uint64_t isWhiteQueens);
    static std::vector<Move> generateKingMoves(uint64_t sameColorPieces, uint64_t isWhiteKing);
};

#endif // MOVEGENERATION_H
