//
// Created by Elias Aggergaard Larsen on 26/09/2024.
//

#define TILESIZE 75
#define LEFTMARGIN 50
#define TOPMARGIN 50
#include "ChessV2.h"

#include <iostream>
#include <thread>
#include "Board.h"
#include "EngineBase/EngineBase.h"

void ChessV2::launch()
{
    int rowNumber = 0;
    for (int i = 0; i < 64; i++)
    {
        EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::WIDTH, TILESIZE});
        EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::HEIGHT, TILESIZE});
        EngineBase::executeCommand({
            PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::X, LEFTMARGIN + (float)(i % 8) * TILESIZE
        });
        EngineBase::executeCommand({
            PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::Y, TOPMARGIN + (float)(i / 8) * TILESIZE
        });
        if ((i % 8 + rowNumber) % 2 == 1)
        {
            EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::TEXTUREINDEX, 1});
        }
        else
        {
            EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::TEXTUREINDEX, 2});
        }
        if (i % 8 == 7)
        {
            rowNumber++;
        }
    }
    std::cout << "Hello, World!" << std::endl;
}

void ChessV2::update(float deltaTime)
{
    // This is currently not needed for the chess game
}
