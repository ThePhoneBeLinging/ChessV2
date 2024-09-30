//
// Created by Elias Aggergaard Larsen on 26/09/2024.
//

#ifndef MOVE_H
#define MOVE_H

#include "Pieces.h"

class Move
{
public:
    Move(uint64_t from, uint64_t to) : from(from), to(to)
    {};

    bool operator==(const Move &rhs) const
    {
        return from == rhs.from && to == rhs.to;
    }

    uint64_t from;
    uint64_t to;
};

#endif //MOVE_H

