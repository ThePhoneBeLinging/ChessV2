//
// Created by Elias Aggergaard Larsen on 29/09/2024.
//

#ifndef DEPTHSEARCH_H
#define DEPTHSEARCH_H
#include "Board.h"


class DepthSearch
{
public:
    static int initializeSearch(Board& board, bool isWhite, int depth);
    static int getAmountOfNodesSearched();

private:
    static int searchRecursive(Board board, bool isWhite, int depth);
    static inline int amountOfNodesSearched_ = 0;
};


#endif //DEPTHSEARCH_H
