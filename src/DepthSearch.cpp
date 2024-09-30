//
// Created by Elias Aggergaard Larsen on 29/09/2024.
//

#include "DepthSearch.h"

int DepthSearch::initializeSearch(Board &board, int depth) {
    return searchRecursive(board, depth);
}

int DepthSearch::countPositionsAtDepth(int depth) {
    Board board = Board();
    return recursiveCountPositionsAtDepth(board, depth);
}

int DepthSearch::searchRecursive(Board board, int depth) {
    if (depth == 0) {
        return 1;
    }
    int max = INT32_MAX;
    int min = INT32_MIN;
    for (const auto &move: board.generateAllLegalMoves()) {
        auto newBoard = Board(board);
        newBoard.executeMove(move);
        int evaluation = searchRecursive(newBoard, depth - 1);
        if (evaluation > max) {
            max = evaluation;
        }
        if (evaluation < min) {
            min = evaluation;
        }
    }

    return board.isWhite_ ? max : min;
}

int DepthSearch::recursiveCountPositionsAtDepth(Board board, int depth) {
    if (depth == 0) {
        return 1;
    }
    int count = 0;
    for (auto &move: board.generateAllLegalMoves()) {
        auto newBoard = Board(board);
        newBoard.executeMove(move);
        count += recursiveCountPositionsAtDepth(newBoard, depth - 1);
    }
    return count;
}
