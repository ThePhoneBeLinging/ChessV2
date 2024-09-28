//
// Created by Elias Aggergaard Larsen on 28/09/2024.
//

#include <gtest/gtest.h>
#include "../src/Board.h"  // Include your Board class header

class BoardTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        board = new Board();
    }

    void TearDown() override
    {
        delete board;
    }

    Board* board;
};

TEST_F(BoardTest, InitialBoardPositions)
{
    // Expected positions for white pieces
    std::vector<std::pair<int, int>> expectedWhitePawns = {
        {0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}
    };
    std::vector<std::pair<int, int>> expectedWhiteRooks = {
        {0, 0}, {7, 0}
    };
    std::vector<std::pair<int, int>> expectedWhiteKnights = {
        {1, 0}, {6, 0}
    };
    std::vector<std::pair<int, int>> expectedWhiteBishops = {
        {2, 0}, {5, 0}
    };
    std::vector<std::pair<int, int>> expectedWhiteQueens = {
        {3, 0}
    };
    std::vector<std::pair<int, int>> expectedWhiteKing = {
        {4, 0}
    };

    // Expected positions for black pieces
    std::vector<std::pair<int, int>> expectedBlackPawns = {
        {0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}, {7, 6}
    };
    std::vector<std::pair<int, int>> expectedBlackRooks = {
        {0, 7}, {7, 7}
    };
    std::vector<std::pair<int, int>> expectedBlackKnights = {
        {1, 7}, {6, 7}
    };
    std::vector<std::pair<int, int>> expectedBlackBishops = {
        {2, 7}, {5, 7}
    };
    std::vector<std::pair<int, int>> expectedBlackQueens = {
        {3, 7}
    };
    std::vector<std::pair<int, int>> expectedBlackKing = {
        {4, 7}
    };

    // Check white pieces
    EXPECT_EQ(board->getAllPieces(Pieces::Pawn, true), expectedWhitePawns);
    EXPECT_EQ(board->getAllPieces(Pieces::Rook, true), expectedWhiteRooks);
    EXPECT_EQ(board->getAllPieces(Pieces::Knight, true), expectedWhiteKnights);
    EXPECT_EQ(board->getAllPieces(Pieces::Bishop, true), expectedWhiteBishops);
    EXPECT_EQ(board->getAllPieces(Pieces::Queen, true), expectedWhiteQueens);
    EXPECT_EQ(board->getAllPieces(Pieces::King, true), expectedWhiteKing);

    // Check black pieces
    EXPECT_EQ(board->getAllPieces(Pieces::Pawn, false), expectedBlackPawns);
    EXPECT_EQ(board->getAllPieces(Pieces::Rook, false), expectedBlackRooks);
    EXPECT_EQ(board->getAllPieces(Pieces::Knight, false), expectedBlackKnights);
    EXPECT_EQ(board->getAllPieces(Pieces::Bishop, false), expectedBlackBishops);
    EXPECT_EQ(board->getAllPieces(Pieces::Queen, false), expectedBlackQueens);
    EXPECT_EQ(board->getAllPieces(Pieces::King, false), expectedBlackKing);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
