//
// Created by Elias Aggergaard Larsen on 26/09/2024.
//


#include "ChessV2.h"

#include <iostream>
#include <memory>
#include <regex>
#include <thread>
#include "Board.h"
#include "EngineBase/EngineBase.h"
#include "Texture/TextureIndices.h"
#include "BoardValues.h"

void ChessV2::launch()
{
    for (int i = 0; i < 128; i++)
    {
        EngineBase::addDrawAble();
    }
    board_ = Board();
    for (int i = 0; i < 64; i++)
    {
        EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::WIDTH, TILESIZE});
        EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::HEIGHT, TILESIZE});
        EngineBase::executeCommand({
            PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::X,
            getDrawLocationFromTile(i % 8, i / 8).first
        });
        EngineBase::executeCommand({
            PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::Y,
            getDrawLocationFromTile(i % 8, i / 8).second
        });
        EngineBase::executeCommand({
            PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::TEXTUREINDEX,
            (int)TextureIndices::EMPTY_BOARD_SQUARE
        });
        EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::Z, 1});
    }

    for (int i = 64; i < 128; i++)
    {
        int rowNumber = i / 8;
        EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::WIDTH, TILESIZE});
        EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::HEIGHT, TILESIZE});
        EngineBase::executeCommand({
            PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::X,
            getDrawLocationFromTile((i - 64) % 8, (i - 64) / 8).first
        });
        EngineBase::executeCommand({
            PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::Y,
            getDrawLocationFromTile((i - 64) % 8, (i - 64) / 8).second
        });
        EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::TEXTUREINDEX, 3});
        if ((i % 8 + rowNumber) % 2 == 1)
        {
            EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::TEXTUREINDEX, 1});
        }
        else
        {
            EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::TEXTUREINDEX, 2});
        }
    }
    EngineBase::executeCommand(Command(PrimaryCMD::DONEWRITING));
    EngineBase::executeCommand(Command(PrimaryCMD::SORTDRAWABLES));
    board_.drawBoard();
}

void ChessV2::handleDrags()
{
    if (board_.draggedPiece_ == nullptr && EngineBase::mouseButtonPressed(ENGINEBASE_BUTTON_LEFT))
    {
        std::pair<int, int> mousePos = EngineBase::getMousePosition();
        mousePos.first = (int)((mousePos.first - LEFTMARGIN) / TILESIZE);
        mousePos.second = (int)((mousePos.second - TOPMARGIN) / TILESIZE);
        if (Board::isPosInsideBoard(mousePos))
        {
            board_.draggedPiece_ = std::make_shared<DraggedPiece>(Board::getBitBoardFromLocation(mousePos));
        }
    }
    if (board_.draggedPiece_ != nullptr)
    {
        uint64_t result = board_.draggedPiece_->updateLocation();
        if (result != 0)
        {
            Move move = {board_.draggedPiece_->getFromLocation(), result};
            bool legalMove = false;
            for (auto& moveToCheckAgainst : board_.generateAllLegalMoves())
            {
                if (move == moveToCheckAgainst)
                {
                    legalMove = true;
                    break;
                }
            }
            if (legalMove)
            {
                board_.executeMove(move);
            }
            board_.draggedPiece_ = nullptr;
            board_.drawBoard();
        }
    }
}

void ChessV2::update(float deltaTime)
{
    handleDrags();
}

std::pair<float, float> ChessV2::getDrawLocationFromTile(int x, int y)
{
    return {LEFTMARGIN + (float)x * TILESIZE, TOPMARGIN + (float)y * TILESIZE};
}

void ChessV2::makeMoveFromNotation(const std::string& notation)
{
    std::regex moveRegex("([a-h][1-8])([a-h][1-8])");
    std::smatch match;
    auto legalMoves = board_.generateAllLegalMoves();
    if (std::regex_match(notation, match, moveRegex))
    {
        std::string from = match[1];
        std::string to = match[2];

        int fromX = from[0] - 'a';
        int fromY = from[1] - '1';
        int toX = to[0] - 'a';
        int toY = to[1] - '1';

        std::pair<int, int> fromPos = {fromX, fromY};
        std::pair<int, int> toPos = {toX, toY};
        Move moveToMake = {Board::getBitBoardFromLocation(fromPos), Board::getBitBoardFromLocation(toPos)};

        if (std::find_if(legalMoves.begin(), legalMoves.end(), [moveToMake](const Move& move)
        {
            return move.from == moveToMake.from && move.to == moveToMake.to;
        }) != legalMoves.end())
        {
            board_.executeMove(moveToMake);
            board_.isWhite_ = not board_.isWhite_;
            std::cout << "Move made: " << notation << std::endl;
        }
        else
        {
            std::cout << "Invalid move: " << notation << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid notation: " << notation << std::endl;
    }
}
