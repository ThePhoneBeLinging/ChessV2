#include <iostream>

#include "ChessV2.h"
#include <thread>
#include "EngineBase/EngineBase.h"

int main()
{
    EngineBase::loadTexture("Resources/green.png");
    EngineBase::loadTexture("Resources/brown.png");
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
