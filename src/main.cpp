#include <iostream>

#include "ChessV2.h"
#include <thread>
#include "EngineBase/EngineBase.h"
#include "Texture/TextureLoader.h"

int main()
{
    EngineBase::loadTexture("Resources/Images/green.png");
    EngineBase::loadTexture("Resources/Images/brown.png");
    EngineBase::loadTexture("invisibleTexture");
    TextureLoader::initializePieceTextures();
    for (int i = 0; i < 128; i++)
    {
        EngineBase::addDrawAble();
    }
    std::thread chessThread(ChessV2::launch);
    EngineBase::startGUI(ChessV2::update);
    chessThread.join();
    std::cout << "Closing App!" << std::endl;
    return 0;
}
