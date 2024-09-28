//
// Created by Elias Aggergaard Larsen on 26/09/2024.
//

#include "Board.h"

#include <iostream>
#include <MacTypes.h>

#include "EngineBase/EngineBase.h"
#include "Texture/TextureIndices.h"

Board::Board()
{
    // Initialize white pieces
    whitePawnsBitBoard_ = 0x000000000000FF00;
    whiteRooksBitBoard_ = 0x0000000000000081;
    whiteKnightsBitBoard_ = 0x0000000000000042;
    whiteBishopsBitBoard_ = 0x0000000000000024;
    whiteQueensBitBoard_ = 0x0000000000000008;
    whiteKingBitBoard_ = 0x0000000000000010;

    // Initialize black pieces
    blackPawnsBitBoard_ = 0x00FF000000000000;
    blackRooksBitBoard_ = 0x8100000000000000;
    blackKnightsBitBoard_ = 0x4200000000000000;
    blackBishopsBitBoard_ = 0x2400000000000000;
    blackQueensBitBoard_ = 0x0800000000000000;
    blackKingBitBoard_ = 0x1000000000000000;
}


std::vector<Move> Board::generateAllLegalMoves(bool isWhite)
{
    std::vector<Move> allMoves;
    std::vector<Move> pseudoLegalMoves;

    uint64_t coloredBitBoard = isWhite ? getWhiteBitBoard() : getBlackBitBoard();

    pseudoLegalMoves = MoveGeneration::generatePawnMoves(coloredBitBoard,
                                                         isWhite ? whitePawnsBitBoard_ : blackPawnsBitBoard_);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = MoveGeneration::generateRookMoves(coloredBitBoard,
                                                         isWhite ? whiteRooksBitBoard_ : blackRooksBitBoard_);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = MoveGeneration::generateKnightMoves(coloredBitBoard,
                                                           isWhite ? whiteKnightsBitBoard_ : blackKnightsBitBoard_);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = MoveGeneration::generateBishopMoves(coloredBitBoard,
                                                           isWhite ? whiteBishopsBitBoard_ : blackBishopsBitBoard_);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = MoveGeneration::generateQueenMoves(coloredBitBoard,
                                                          isWhite ? whiteQueensBitBoard_ : blackQueensBitBoard_);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = MoveGeneration::generateKingMoves(coloredBitBoard,
                                                         isWhite ? whiteKingBitBoard_ : blackKingBitBoard_);
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

std::vector<std::pair<int, int>> Board::getAllPieces(Pieces piece, bool isWhite)
{
    uint64_t bitBoard = 0;
    switch (piece)
    {
    case Pieces::Pawn:
        bitBoard = isWhite ? whitePawnsBitBoard_ : blackPawnsBitBoard_;
        break;
    case Pieces::Rook:
        bitBoard = isWhite ? whiteRooksBitBoard_ : blackRooksBitBoard_;
        break;
    case Pieces::Knight:
        bitBoard = isWhite ? whiteKnightsBitBoard_ : blackKnightsBitBoard_;
        break;
    case Pieces::Bishop:
        bitBoard = isWhite ? whiteBishopsBitBoard_ : blackBishopsBitBoard_;
        break;
    case Pieces::Queen:
        bitBoard = isWhite ? whiteQueensBitBoard_ : blackQueensBitBoard_;
        break;
    case Pieces::King:
        bitBoard = isWhite ? whiteKingBitBoard_ : blackKingBitBoard_;
        break;
    default:
        throw std::invalid_argument("Invalid piece type or color");
    }

    std::vector<std::pair<int, int>> locations;

    for (int i = 0; i < 64; ++i)
    {
        if (bitBoard & (1ULL << i))
        {
            int x = i % 8;
            int y = 7 - (i / 8);
            locations.emplace_back(x, y);
        }
    }
    return locations;
}

void Board::drawBoard()
{
    // TODO Effectivise this:
    for (int i = 0; i < 64; i++)
    {
        EngineBase::executeCommand({
            PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::TEXTUREINDEX,
            (float)TextureIndices::EMPTY_BOARD_SQUARE
        });
    }
    TextureIndices textureToUse = TextureIndices::EMPTY_BOARD_SQUARE;
    for (int i = 0; i < 12; i++)
    {
        bool isWhite = i > 5;
        std::vector<std::pair<int, int>> vectorOfPairs;
        switch (i % 6)
        {
        case 0:
            {
                vectorOfPairs = getAllPieces(Pieces::Pawn, isWhite);
                textureToUse = isWhite ? TextureIndices::WHITE_PAWN : TextureIndices::BLACK_PAWN;
                break;
            }
        case 1:
            {
                vectorOfPairs = getAllPieces(Pieces::Knight, isWhite);
                textureToUse = isWhite ? TextureIndices::WHITE_KNIGHT : TextureIndices::BLACK_KNIGHT;
                break;
            }
        case 2:
            {
                vectorOfPairs = getAllPieces(Pieces::Bishop, isWhite);
                textureToUse = isWhite ? TextureIndices::WHITE_BISHOP : TextureIndices::BLACK_BISHOP;
                break;
            }
        case 3:
            {
                vectorOfPairs = getAllPieces(Pieces::Rook, isWhite);
                textureToUse = isWhite ? TextureIndices::WHITE_ROOK : TextureIndices::BLACK_ROOK;
                break;
            }
        case 4:
            {
                vectorOfPairs = getAllPieces(Pieces::King, isWhite);
                textureToUse = isWhite ? TextureIndices::WHITE_KING : TextureIndices::BLACK_KING;
                break;
            }
        case 5:
            {
                vectorOfPairs = getAllPieces(Pieces::Queen, isWhite);
                textureToUse = isWhite ? TextureIndices::WHITE_QUEEN : TextureIndices::BLACK_QUEEN;
                break;
            }
        }
        for (auto pairs : vectorOfPairs)
        {
            EngineBase::executeCommand({
                PrimaryCMD::UPDATE, ObjectType::DRAWABLE, pairs.first + pairs.second * 8, SecondaryCMD::TEXTUREINDEX,
                (float)textureToUse
            });
        }
    }
}

uint64_t Board::getWhiteBitBoard() const
{
    return whitePawnsBitBoard_ | whiteRooksBitBoard_ | whiteKnightsBitBoard_ | whiteBishopsBitBoard_ |
        whiteQueensBitBoard_ | whiteKingBitBoard_;
}

uint64_t Board::getBlackBitBoard() const
{
    return blackPawnsBitBoard_ | blackRooksBitBoard_ | blackKnightsBitBoard_ | blackBishopsBitBoard_ |
        blackQueensBitBoard_ | blackKingBitBoard_;
}

bool Board::isMoveLegal(const Move& move, bool isWhite)
{
    // TODO Implement logic to check if a move is legal (does not leave the king in check)
    return true;
}
