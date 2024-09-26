//
// Created by Elias Aggergaard Larsen on 26/09/2024.
//

#ifndef CHESSV2_H
#define CHESSV2_H
#include <cstdint>
#include <utility>


class ChessV2
{
public:
    static void launch();
    static void update(float deltaTime);

private:
    static std::pair<float, float> getDrawLocationFromTile(int x, int y);
};


#endif //CHESSV2_H
