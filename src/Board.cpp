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

    pseudoLegalMoves = generateAllPawnMoves(isWhite);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = generateAllRookMoves(isWhite);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = generateAllKnightMoves(isWhite);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = generateAllBishopMoves(isWhite);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = generateAllQueenMoves(isWhite);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = generateAllKingMoves(isWhite);
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

uint64_t Board::getBitBoardFromLocation(std::pair<int, int> location)
{
    return 1ULL << (location.first + location.second * 8);
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

bool Board::isTileOccupiedByColor(std::pair<int, int> location, bool isWhite) const
{
    auto bitBoardOfPos = getBitBoardFromLocation(location);
    auto bitBoardOfColor = isWhite ? getWhiteBitBoard() : getBlackBitBoard();
    return bitBoardOfPos & bitBoardOfColor;
}

bool Board::isPosInsideBoard(std::pair<int, int> location)
{
    return location.first >= 0 && location.first < 8 && location.second >= 0 && location.second < 8;
}

std::vector<Move> Board::generateAllPawnMoves(bool isWhite)
{
    std::vector<Move> moves;
    auto locationOfPieces = getAllPieces(Pieces::Pawn, isWhite);
    for (auto& pair : locationOfPieces)
    {
        std::vector<std::pair<int, int>> legalPositions;
        std::pair<int, int> newLocation = {pair.first, pair.second};
        // Check if the pawn can move one step forward
        newLocation.second += (isWhite ? 1 : -1);
        if (not isTileOccupiedByColor(newLocation, true) && not isTileOccupiedByColor(newLocation, false)
            && isPosInsideBoard(newLocation))
        {
            moves.push_back({getBitBoardFromLocation(pair), getBitBoardFromLocation(newLocation)});
            continue;
        }
        // Check if the pawn can move two steps forward
        newLocation.second += (isWhite ? 1 : -1);
        if (pair.first == (isWhite ? 1 : 6) && not isTileOccupiedByColor(newLocation, true)
            && not isTileOccupiedByColor(newLocation, false))
        {
            moves.push_back({getBitBoardFromLocation(pair), getBitBoardFromLocation(newLocation)});
            continue;
        }
        // Resets newLocation
        newLocation = {pair.first, pair.second};
        // Check if the pawn can capture a piece
        newLocation = {pair.first + (isWhite ? 1 : -1), pair.second + (isWhite ? 1 : -1)};
        if (isTileOccupiedByColor(newLocation, false) && isPosInsideBoard(newLocation))
        {
            moves.push_back({getBitBoardFromLocation(pair), getBitBoardFromLocation(newLocation)});
            continue;
        }
    }
    return moves;
}

std::vector<Move> Board::generateAllRookMoves(bool isWhite)
{
    std::vector<Move> moves;

    auto locationOfPieces = getAllPieces(Pieces::Rook, isWhite);
    for (auto& pair : locationOfPieces)
    {
        for (int i = -pair.first; i < 8 - pair.first; i++)
        {
            if (i == 0)
            {
                continue;
            }
            std::pair<int, int> newLocation = {pair.first + i, pair.second};
            if (isTileOccupiedByColor(newLocation, true))
            {
                break;
            }
            moves.push_back({getBitBoardFromLocation(pair), getBitBoardFromLocation(newLocation)});
            if (isTileOccupiedByColor(newLocation, false))
            {
                break;
            }
        }
        for (int i = -pair.second; i < 8 - pair.second; i++)
        {
            if (i == 0)
            {
                continue;
            }
            std::pair<int, int> newLocation = {pair.first, pair.second + i};
            if (isTileOccupiedByColor(newLocation, true))
            {
                break;
            }
            moves.push_back({getBitBoardFromLocation(pair), getBitBoardFromLocation(newLocation)});
            if (isTileOccupiedByColor(newLocation, false))
            {
                break;
            }
        }
    }
    return moves;
}

std::vector<Move> Board::generateAllKnightMoves(bool isWhite)
{
    std::vector<Move> moves;

    auto locationOfPieces = getAllPieces(Pieces::Knight, isWhite);

    for (auto& pair : locationOfPieces)
    {
        std::vector<std::pair<int, int>> possibleMoves =
        {
            {pair.first + 1, pair.second + 2},
            {pair.first + 1, pair.second - 2},
            {pair.first - 1, pair.second + 2},
            {pair.first - 1, pair.second - 2},
            {pair.first + 2, pair.second + 1},
            {pair.first + 2, pair.second - 1},
            {pair.first - 2, pair.second + 1},
            {pair.first - 2, pair.second - 1}
        };

        for (auto& newLocation : possibleMoves)
        {
            if (isTileOccupiedByColor(newLocation, true))
            {
                continue;
            }
            moves.push_back({getBitBoardFromLocation(pair), getBitBoardFromLocation(newLocation)});
        }
    }

    return moves;
}

std::vector<Move> Board::generateAllBishopMoves(bool isWhite)
{
    std::vector<Move> moves;
    auto locationOfPieces = getAllPieces(Pieces::Bishop, isWhite);

    for (auto& pair : locationOfPieces)
    {
        for (int i = -8; i < 8; i++)
        {
            std::pair<int, int> newLocation = {pair.first + i, pair.second + i};
            if (i == 0 || isPosInsideBoard(newLocation))
            {
                continue;
            }
            if (isTileOccupiedByColor(newLocation, true))
            {
                break;
            }
            moves.push_back({getBitBoardFromLocation(pair), getBitBoardFromLocation(newLocation)});
            if (isTileOccupiedByColor(newLocation, false))
            {
                break;
            }
        }
    }

    return moves;
}

std::vector<Move> Board::generateAllQueenMoves(bool isWhite)
{
}

std::vector<Move> Board::generateAllKingMoves(bool isWhite)
{
}
