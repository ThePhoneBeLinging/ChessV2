//
// Created by Elias Aggergaard Larsen on 29/09/2024.
//

#ifndef DEPTHSEARCH_H
#define DEPTHSEARCH_H

#include "Board.h"


class DepthSearch
{
public:
    static int initializeSearch(Board& board, int depth);

    static int countPositionsAtDepth(int depth);

private:
    static int searchRecursive(Board board, int depth);

    static void recursiveCountPositionsAtDepth(Board board, int depth, int* count);
};


#endif //DEPTHSEARCH_H
