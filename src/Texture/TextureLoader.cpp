//
// Created by Elias Aggergaard Larsen on 27/09/2024.
//

#include "TextureLoader.h"

#include "EngineBase/EngineBase.h"

void TextureLoader::initializePieceTextures()
{
    auto constantPath = "Resources/Images/Pieces/";
    std::vector<std::string> prefix = {"W", "B"};
    std::vector<std::string> pieces = {"Pawn", "Rook", "Knight", "Bishop", "Queen", "King"};

    for (const auto& p : prefix)
    {
        for (const auto& piece : pieces)
        {
            auto customPath = p + piece;
            customPath.append(".png");
            EngineBase::loadTexture(constantPath + customPath);
        }
    }
}
