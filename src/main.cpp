#include <iostream>

#include "ChessV2.h"
#include <thread>
#include "EngineBase/EngineBase.h"

int main()
{
    std::thread chessThread(ChessV2::launch);
    EngineBase::startGUI(ChessV2::update);
    chessThread.join();
    std::cout << "Closing App!" << std::endl;
    return 0;
}
