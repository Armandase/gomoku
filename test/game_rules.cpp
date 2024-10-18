#include "../inc/Game.hpp"
#include "../inc/ClassicBoard.hpp"
#include <algorithm>
#include <gtest/gtest.h>

TEST(IBoardTest, doubleThree) {
        std::string str_test(
"0000000000000000000"
"0100100100000000000"
"0010101000000000000"
"0000000000000000000"
"0110001100000000000"
"0000000000000000000"
"0010101000000000000"
"0100100100000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000");
    std::reverse(str_test.begin(), str_test.end());
    IBoard::bitboard test(str_test);

    Game gameTest;
    int size = test.size();
    int width = gameTest.getClassicBoard().getWidth();
    for (int i = 0; i < size; i++){
        if (!test[i])
            continue;
        gameTest.setPosToBoards(i % width, i / width, test[i]);
    }
    gameTest.setPosToBoards(8, 4, BLACK);
    EXPECT_EQ(gameTest.isDoubleThree(4, 4, WHITE), true);
}