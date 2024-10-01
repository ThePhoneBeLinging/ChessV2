//
// Created by Elias Aggergaard Larsen on 29/09/2024.
//

#include "DepthSearch.h"

#include <thread>

int DepthSearch::initializeSearch(Board &board, int depth)
{
    return searchRecursive(board, depth);
}

int DepthSearch::countPositionsAtDepth(int depth)
{
    auto legalMoves = Board().generateAllLegalMoves();
    Board board = Board();
    std::vector<int> result(legalMoves.size(), 0);
    std::vector<std::thread> threads;
    threads.resize(legalMoves.size());
    for (int i = 0; i < legalMoves.size(); i++)
    {
        Board newBoard = Board(board);
        newBoard.executeMove(legalMoves[i]);
        threads[i] = std::thread(recursiveCountPositionsAtDepth, newBoard, depth - 1, &result[i]);
    }

    int totalCount = 0;

    for (int i = 0; i < legalMoves.size(); i++)
    {
        threads[i].join();
        totalCount += result[i];
    }
    return totalCount;
}

int DepthSearch::searchRecursive(Board board, int depth)
{
    if (depth == 0)
    {
        return 1;
    }
    int max = INT32_MAX;
    int min = INT32_MIN;
    for (const auto &move: board.generateAllLegalMoves())
    {
        auto newBoard = Board(board);
        newBoard.executeMove(move);
        int evaluation = searchRecursive(newBoard, depth - 1);
        if (evaluation > max)
        {
            max = evaluation;
        }
        if (evaluation < min)
        {
            min = evaluation;
        }
    }

    return board.isWhite_ ? max : min;
}

void DepthSearch::recursiveCountPositionsAtDepth(Board board, int depth, int *count)
{
    if (depth == 0)
    {
        (*count)++;
        return;
    }
    for (auto &move: board.generateAllLegalMoves())
    {
        auto newBoard = Board(board);
        newBoard.executeMove(move);
        recursiveCountPositionsAtDepth(newBoard, depth - 1, count);
    }
}
