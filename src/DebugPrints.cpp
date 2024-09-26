//
// Created by Elias Aggergaard Larsen on 26/09/2024.
//

#include "DebugPrints.h"

#include <iostream>

void DebugPrints::printMatrix(uint64_t value)
{
    std::bitset<64> bits(value);
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            std::cout << bits[63 - (row * 8 + col)] << " ";
        }
        std::cout << std::endl;
    }
}
