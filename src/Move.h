//
// Created by Elias Aggergaard Larsen on 26/09/2024.
//

#ifndef MOVE_H
#define MOVE_H

class Move
{
public:
    Move(uint64_t from, uint64_t to) : from(from), to(to)
    {
    };

    bool operator==(const Move& rhs) const
    {
        return from == rhs.from && to == rhs.to;
    }

    uint64_t from;
    uint64_t to;
    uint64_t capturedPiece = 0;
};

#endif //MOVE_H

