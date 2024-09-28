//
// Created by Elias Aggergaard Larsen on 26/09/2024.
//

#ifndef MOVE_H
#define MOVE_H

#include "Pieces.h"

typedef struct Move
{
    // Only the position of the piece
    uint64_t from;
    uint64_t to;
} Move;

#endif //MOVE_H

