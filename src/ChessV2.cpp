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
    for (int i = 0; i < 64; i++)
    {
        EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::WIDTH, TILESIZE});
        EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::HEIGHT, TILESIZE});
        EngineBase::executeCommand({
            PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::X, getDrawLocationFromTile(i % 8, i / 8).first
        });
        EngineBase::executeCommand({
            PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::Y, getDrawLocationFromTile(i % 8, i / 8).second
        });
        EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::TEXTUREINDEX, 3});
        EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::Z, 1});
    }
    // This is a hack to force EngineBase to sort the DrawAbles based on Z value
    EngineBase::addDrawAble();

    for (int i = 64; i < 128; i++)
    {
        int rowNumber = i / 8;
        EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::WIDTH, TILESIZE});
        EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::HEIGHT, TILESIZE});
        EngineBase::executeCommand({
            PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::X,
            getDrawLocationFromTile((i - 64) % 8, (i - 64) / 8).first
        });
        EngineBase::executeCommand({
            PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::Y,
            getDrawLocationFromTile((i - 64) % 8, (i - 64) / 8).second
        });
        EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::TEXTUREINDEX, 3});
        if ((i % 8 + rowNumber) % 2 == 1)
        {
            EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::TEXTUREINDEX, 1});
        }
        else
        {
            EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, i, SecondaryCMD::TEXTUREINDEX, 2});
        }
    }
}

void ChessV2::update(float deltaTime)
{
    // This is currently not needed for the chess game
}

std::pair<float, float> ChessV2::getDrawLocationFromTile(int x, int y)
{
    return {LEFTMARGIN + (float)x * TILESIZE, TOPMARGIN + (float)y * TILESIZE};
}
