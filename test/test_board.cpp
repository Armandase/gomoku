#include "../inc/Game.hpp"
#include "../inc/ClassicBoard.hpp"
#include <algorithm>
#include <gtest/gtest.h>

TEST(IBoard, TestTransposedBoard){
    IBoard::bitboard test(
"0111110000000000000"
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
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000");

    IBoard::bitboard waited_result(
"0000000000000000000"
"1000000000000000000"
"1000000000000000000"
"1000000000000000000"
"1000000000000000000"
"1000000000000000000"
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
"0000000000000000000"
"0000000000000000000"
"0000000000000000000");

    Game gameTest;
    int player = 0;
    int width = gameTest.getClassicBoard().getWidth();
    for (int i = 0; i < test.size(); i++){
        if (!test[i])
            continue;
        gameTest.setPosToBoards(i % width, i / width, 1);
    }
    
    EXPECT_EQ(gameTest.getTransposedBoard().getPlayer1(), waited_result);
}

TEST(IBoard, TestDiagBoard){

    std::string str_test(
"0000000000000001000"
"0000000000000010000"
"0000000000000100000"
"0000000000001000000"
"0000000000010000000"
"0000000000100000000"
"0000000001000000000"
"0000000010000000000"
"0000000100000000000"
"0000001000000000000"
"0000010000000000000"
"0000100000000000000"
"0001000000000000000"
"0010000000000000000"
"0100000000000000000"
"1000000000000000000"
"0000000000000000000"
"0000000000000000000"
"1111111111111111111");
    std::reverse(str_test.begin(), str_test.end());
    IBoard::bitboard test(str_test);

    std::string str_result(
"0100000000000000000"
"0010000000000000000"
"0001000000000000000"
"0000100000000000000"
"0000010000000000000"
"0000001000000000000"
"0000000100000000000"
"0000000010000000000"
"0000000001000000000"
"0000000000100000000"
"0000000000010000000"
"0000000000001000000"
"0000000000000100000"
"0000000000000010000"
"0000000000000001000"
"1111111111111111100"
"0000000000000000010"
"0000000000000000001"
"1000000000000000000");
    std::reverse(str_result.begin(), str_result.end());
    IBoard::bitboard waited_result(str_result);


    Game gameTest;
    int player = 0;
    int width = gameTest.getDiagBoard().getWidth();
    for (int i = 0; i < test.size(); i++){
        if (!test[i])
            continue;
        gameTest.setPosToBoards(i % width, i / width, 1);
    }
    
    EXPECT_EQ(gameTest.getDiagBoard().getPlayer1(), waited_result);
}

TEST(IBoard, TestAntiDiagBoard){

    std::string str_test(
"1111111111111111111"
"0000000000000000000"
"0000000000000000000"
"1000000000000000000"
"0100000000000000000"
"0010000000000000000"
"0001000000000000000"
"0000100000000000000"
"0000010000000000000"
"0000001000000000000"
"0000000100000000000"
"0000000010000000000"
"0000000001000000000"
"0000000000100000000"
"0000000000010000000"
"0000000000001000000"
"0000000000000100000"
"0000000000000010000"
"0000000000000001000");
    std::reverse(str_test.begin(), str_test.end());
    IBoard::bitboard test(str_test);

    std::string str_result(
"1000000000000000000"
"0000000000000000001"
"0000000000000000010"
"1111111111111111100"
"0000000000000001000"
"0000000000000010000"
"0000000000000100000"
"0000000000001000000"
"0000000000010000000"
"0000000000100000000"
"0000000001000000000"
"0000000010000000000"
"0000000100000000000"
"0000001000000000000"
"0000010000000000000"
"0000100000000000000"
"0001000000000000000"
"0010000000000000000"
"0100000000000000000");
    std::reverse(str_result.begin(), str_result.end());
    IBoard::bitboard waited_result(str_result);


    Game gameTest;
    int player = 0;
    int width = gameTest.getDiagBoard().getWidth();
    for (int i = 0; i < test.size(); i++){
        if (!test[i])
            continue;
        gameTest.setPosToBoards(i % width, i / width, 1);
    }
    
    EXPECT_EQ(gameTest.getAntiDiagBoard().getPlayer1(), waited_result);
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