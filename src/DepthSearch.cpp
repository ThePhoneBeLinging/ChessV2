//
// Created by Elias Aggergaard Larsen on 29/09/2024.
//

#include "DepthSearch.h"

int DepthSearch::initializeSearch(Board& board, bool isWhite, int depth)
{
    return searchRecursive(board, isWhite, depth);
}

int DepthSearch::countPositionsAtDepth(int depth)
{
    Board board = Board();
    return recursiveCountPositionsAtDepth(board, true, depth);
}

int DepthSearch::searchRecursive(Board board, bool isWhite, int depth)
{
    if (depth == 0)
    {
        return 1;
    }
    int max = INT32_MAX;
    int min = INT32_MIN;
    for (const auto& move : board.generateAllLegalMoves(isWhite))
    {
        auto newBoard = Board(board);
        newBoard.executeMove(move);
        int evaluation = searchRecursive(newBoard, not isWhite, depth - 1);
        if (evaluation > max)
        {
            max = evaluation;
        }
        if (evaluation < min)
        {
            min = evaluation;
        }
    }

    return isWhite ? max : min;
}

int DepthSearch::recursiveCountPositionsAtDepth(Board board, bool isWhite, int depth)
{
    if (depth == 0)
    {
        return 1;
    }
    int count = 0;
    for (auto& move : board.generateAllLegalMoves(isWhite))
    {
        auto newBoard = Board(board);
        newBoard.executeMove(move);
        count += recursiveCountPositionsAtDepth(newBoard, not isWhite, depth - 1);
    }
    return count;
}
