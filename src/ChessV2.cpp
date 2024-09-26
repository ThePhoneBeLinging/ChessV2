//
// Created by Elias Aggergaard Larsen on 26/09/2024.
//

#include "ChessV2.h"

#include <iostream>
#include <thread>

#include "Board.h"
#include "EngineBase/EngineBase.h"

void ChessV2::launch()
{
    EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, 0, SecondaryCMD::WIDTH, 50});
    EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, 0, SecondaryCMD::HEIGHT, 50});
    std::cout << "Hello, World!" << std::endl;
}

void ChessV2::update(float deltaTime)
{
    // This is currently not needed for the chess game
}
