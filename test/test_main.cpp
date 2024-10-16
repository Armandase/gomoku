#include "../inc/gomoku.hpp"
#include "../inc/Game.hpp"
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
    Game gameTest;

    EXPECT_EQ(gameTest.getClassicBoard().isValidPos(0, gameTest.getClassicBoard().getWidth() - 1), true);
    EXPECT_EQ(gameTest.getClassicBoard().isValidPos(1, gameTest.getClassicBoard().getWidth() - 2), true);
    EXPECT_EQ(gameTest.getClassicBoard().isValidPos(-15, gameTest.getClassicBoard().getWidth() - 2), false);
    EXPECT_EQ(gameTest.getClassicBoard().isValidPos( 2, gameTest.getClassicBoard().getWidth() ), false);
}

// JSP POURQUOI IL MARCHE PAS LUI
TEST(Board_setPos, TestSetPos){
    Game gameTest;

    int x = 0;
    int y = gameTest.getClassicBoard().getWidth() - 1;
    
    gameTest.getClassicBoard().setPos(x, y, WHITE);
    EXPECT_EQ(gameTest.getClassicBoard().getPos(x, y), WHITE);
    
    gameTest.getClassicBoard().setPos(x, y, BLACK);
    EXPECT_EQ(gameTest.getClassicBoard().getPos(x, y), WHITE);

    x = 100000, y = 100000;
    gameTest.getClassicBoard().setPos(x, y, WHITE);
    EXPECT_EQ(gameTest.getClassicBoard().getPos(x, y), 0);
}

TEST(ClassicBoard, TestSetPos){
    ClassicBoard classicBoard;

    int x = 0;
    int y = classicBoard.getWidth() - 1;
    
    classicBoard.setPos(x, y, WHITE);
    EXPECT_EQ(classicBoard.getPos(x, y), WHITE);
    
    classicBoard.setPos(x, y, BLACK);
    EXPECT_EQ(classicBoard.getPos(x, y), WHITE);

    x = 100000, y = 100000;
    classicBoard.setPos(x, y, WHITE);
    EXPECT_EQ(classicBoard.getPos(x, y), 0);
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