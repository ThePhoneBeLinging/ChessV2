//
// Created by Elias Aggergaard Larsen on 26/09/2024.
//

#ifndef CHESSV2_H
#define CHESSV2_H
#include <cstdint>
#include <string>
#include <utility>

#include "Board.h"


class ChessV2
{
public:
    static void launch();
    static void update(float deltaTime);

private:
    static void handleInput();
    static std::pair<float, float> getDrawLocationFromTile(int x, int y);
    static void makeMoveFromNotation(const std::string& notation);
    static inline Board board_;
    static inline bool isWhite_;
};


#endif //CHESSV2_H
