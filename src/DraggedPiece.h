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
    explicit DraggedPiece(uint64_t fromLocation);

    uint64_t updateLocation();

    [[nodiscard]] uint64_t getFromLocation() const;

private:
    uint64_t fromLocation_;
    std::pair<int, int> location_;
    std::pair<int, int> offset_;
    int idToUpdate_;
};


#endif //CHESSV2_DRAGGEDPIECE_H
