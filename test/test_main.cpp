#include "../inc/gomoku.hpp"
#include "../inc/Board.hpp"
#include <gtest/gtest.h>

TEST(HandleMouse, TestOut) {
    EXPECT_EQ(handleMouse(-15, MARGIN + BOARD_DIMENSIONS), false);
    EXPECT_EQ(handleMouse(-15, MARGIN + BOARD_DIMENSIONS + 100), false);
    EXPECT_EQ(handleMouse(MARGIN + BOARD_DIMENSIONS + 1000, -100), false);
    EXPECT_EQ(handleMouse(MARGIN + BOARD_DIMENSIONS + 1, MARGIN + BOARD_DIMENSIONS + 1), false);
}

TEST(HandleMouse, TestIn) {
    EXPECT_EQ(handleMouse(MARGIN, MARGIN), true);
    EXPECT_EQ(handleMouse(MARGIN, MARGIN + BOARD_DIMENSIONS), true);
    EXPECT_EQ(handleMouse(MARGIN + BOARD_DIMENSIONS, MARGIN), true);
    EXPECT_EQ(handleMouse(MARGIN + BOARD_DIMENSIONS, MARGIN + BOARD_DIMENSIONS), true);
}

TEST(Board_isValidPos, TestValidPos){
    Board gameTest;

    EXPECT_EQ(gameTest.isValidPos(0, gameTest.getWidth() - 1), true);
    EXPECT_EQ(gameTest.isValidPos(1, gameTest.getWidth() - 2), true);
    EXPECT_EQ(gameTest.isValidPos(-15, gameTest.getWidth() - 2), false);
    EXPECT_EQ(gameTest.isValidPos( 2, gameTest.getWidth() ), false);
}

TEST(Board_setPos, TestSetPos){
    Board gameTest;

    int x = 0;
    int y = gameTest.getWidth() - 1;
    
    gameTest.setPos(x, y, WHITE);
    EXPECT_EQ(gameTest.getPos(x, y), WHITE);
    
    gameTest.setPos(x, y, BLACK);
    EXPECT_EQ(gameTest.getPos(x, y), WHITE);

    x = 100000, y = 100000;
    gameTest.setPos(x, y, WHITE);
    EXPECT_EQ(gameTest.getPos(x, y), 0);
}


// TEST(Board_extractPatterns, TestInputExtraction){
//     Board::bitboard test(
// "0000000000000000000"
// "0000000000000000000"
// "0000000000000000000"
// "0001001000000000000"
// "0000000000000000000"
// "0000011000000000000"
// "0001011000000000000"
// "0000011000000000000"
// "0000000000000000000"
// "0001001000000000000"
// "0000000000000000000"
// "0000000000000000000"
// "0000000000000000000"
// "0000000000000000000"
// "0000000000000000000"
// "0000000000000000000"
// "0000000000000000000"
// "0000000000000000000"
// "0000000000000000000");

//     Board gameTest;
//     int player = 0;
//     for (int i = 0; i < test.size(); i++){
//         if (!test[i])
//             continue;
//         std::cout << "Pos to place x:" << i % gameTest.getWidth() << " y: " << i / gameTest.getWidth() << std::endl;
//         gameTest.setPos(i % gameTest.getWidth(), i / gameTest.getWidth(), test[i]);
//     }
    
//     Board::patternMap waitedResult;
//     patternBitset pattern("1011");
//     waitedResult.insert(Board::patternPair(Board::PatternType::DEFAULT,pattern));
//     waitedResult.insert(Board::patternPair(Board::PatternType::TRANSPOS, pattern));
//     waitedResult.insert(Board::patternPair(Board::PatternType::DIAG, pattern));
//     waitedResult.insert(Board::patternPair(Board::PatternType::ANTIDIAG, pattern));

//     EXPECT_EQ(gameTest.extractPatterns(19-7, 19-7, 5, 1), waitedResult);
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}