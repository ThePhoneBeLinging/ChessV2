//
// Created by Elias on 30/09/2024.
//

#ifndef CHESSV2_DRAGGEDPIECE_H
#define CHESSV2_DRAGGEDPIECE_H


#include <cstdint>
#include <utility>

class DraggedPiece
{
public:
    DraggedPiece(int initialX, int initialY);

    void updateLocation();

private:
    uint64_t fromLocation;
    std::pair<int, int> location_;
};


#endif //CHESSV2_DRAGGEDPIECE_H
