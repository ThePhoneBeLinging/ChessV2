//
// Created by Elias Aggergaard Larsen on 26/09/2024.
//

#include "ChessV2.h"

#include <iostream>
#include <thread>

#include "Board.h"

void ChessV2::launch()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Board();
    std::cout << "Hello, World!" << std::endl;
}

void ChessV2::update(float deltaTime)
{
    // This is currently not needed for the chess game
}
