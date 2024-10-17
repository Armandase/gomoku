#include "../inc/Game.hpp"
#include "../inc/ClassicBoard.hpp"
#include <algorithm>
#include <gtest/gtest.h>

TEST(IBoardTest, TestTransposedBoard){
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
    int width = gameTest.getClassicBoard().getWidth();
    int size = test.size();
    for (int i = 0; i < size; i++){
        if (!test[i])
            continue;
        gameTest.setPosToBoards(i % width, i / width, 1);
    }
    
    EXPECT_EQ(gameTest.getTransposedBoard().getPlayer1(), waited_result);
}

TEST(IBoardTest, TestDiagBoard){

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
    int size = test.size();
    int width = gameTest.getDiagBoard().getWidth();
    for (int i = 0; i < size; i++){
        if (!test[i])
            continue;
        gameTest.setPosToBoards(i % width, i / width, 1);
    }
    
    EXPECT_EQ(gameTest.getDiagBoard().getPlayer1(), waited_result);
}

TEST(IBoardTest, TestAntiDiagBoard){

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


TEST(ClassicBoardTest, extractPattern){
    std::string str_test(
"0000000000000000000"
"0101100000000000010"
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
    std::reverse(str_test.begin(), str_test.end());
    IBoard::bitboard test(str_test);

    ClassicBoard board;

    int size = test.size();
    int width = board.getWidth();
    for (int i = 0; i < size; i++){
        if (!test[i])
            continue;
        board.setPos(i % width, i / width, test[i]);
    }
    
    {
        patternBitset  waitedResult("1101");

        EXPECT_EQ(board.extractPattern(1, 1, 4, 1), waitedResult);
    }
    {
        patternBitset  waitedResult("1101");

        EXPECT_EQ(board.extractPatternReversed(5, 1, 4, 1), waitedResult);
    }

    {
        patternBitset  waitedResult("0000");
        EXPECT_EQ(board.extractPattern(width-3, 1, 4, 1), waitedResult);
    }

    {
        patternBitset  waitedResult("0001");
        EXPECT_EQ(board.extractPattern(width-2, 1, 1, 1), waitedResult);
    }
}

TEST(TransposedBoardTest, extractPattern){
    std::string str_test(
"0000000000000000000"
"0101100000000000000"
"0100000000000000000"
"0100000000000000000"
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
    std::reverse(str_test.begin(), str_test.end());
    IBoard::bitboard test(str_test);

    TransposedBoard board;

    int size = test.size();
    int width = board.getWidth();
    for (int i = 0; i < size; i++){
        if (!test[i])
            continue;
        board.setPos(i % width, i / width, test[i]);
    }
    
    {
        patternBitset  waitedResult("0111");

        EXPECT_EQ(board.extractPattern(1, 1, 4, 1), waitedResult);
    }
    {
        patternBitset  waitedResult("0111");

        EXPECT_EQ(board.extractPatternReversed(5, 1, 4, 1), waitedResult);
    }
}

TEST(DiagBoardTest, extractPattern){
    std::string str_test(
"0000000000000000000"
"0101100000000000000"
"0100000000000000000"
"0101000000000000000"
"0000100000000000000"
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
    std::reverse(str_test.begin(), str_test.end());
    IBoard::bitboard test(str_test);

    DiagBoard board;

    int size = test.size();
    int width = board.getWidth();
    for (int i = 0; i < size; i++){
        if (!test[i])
            continue;
        board.setPos(i % width, i / width, test[i]);
    }
    
    {
        patternBitset  waitedResult("0000");
        //Doit etre null car l'extraction est trop grande par rapport aux coordonnes (ca sort du plateau)
        EXPECT_EQ(board.extractPattern(1, 1, 4, 1), waitedResult);
    }
    {
        patternBitset  waitedResult("0010");
        EXPECT_EQ(board.extractPattern(0, 3, 4, 1), waitedResult);
    }
    {
        patternBitset  waitedResult("0000");
        //Doit etre null car l'extraction est trop grande par rapport aux coordonnes (ca sort du plateau)
        EXPECT_EQ(board.extractPatternReversed(5, 1, 4, 1), waitedResult);
    }
    {
        patternBitset  waitedResult("0010");
        EXPECT_EQ(board.extractPatternReversed(4, 3, 4, 1), waitedResult);
    }

}

TEST(AntiDiagBoardTest, extractPattern){
    std::string str_test(
"0000000000000000000"
"0101100000000000000"
"0100000000000000000"
"0101000000000000000"
"0000100000000000000"
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
    std::reverse(str_test.begin(), str_test.end());
    IBoard::bitboard test(str_test);

    AntiDiagBoard board;

    int size = test.size();
    int width = board.getWidth();
    for (int i = 0; i < size; i++){
        if (!test[i])
            continue;
        board.setPos(i % width, i / width, test[i]);
    }
    {
        patternBitset  waitedResult("0000");
        //Doit etre null car l'extraction est trop grande par rapport aux coordonnes (ca sort du plateau)
        EXPECT_EQ(board.extractPattern(2, 4, 4, 1), waitedResult);
    }
    {
        patternBitset  waitedResult("1101");
        EXPECT_EQ(board.extractPattern(1, 1, 4, 1), waitedResult);
    }
    {
        patternBitset  waitedResult("0000");
        //Doit etre null car l'extraction est trop grande par rapport aux coordonnes (ca sort du plateau)
        EXPECT_EQ(board.extractPatternReversed(6, 4, 4, 1), waitedResult);
    }
    {
        patternBitset  waitedResult("1101");
        EXPECT_EQ(board.extractPatternReversed(5, 1, 4, 1), waitedResult);
    }
}

TEST(IBoardTest, doubleThree) {
        std::string str_test(
"0000000000000000000"
"0000000000000000000"
"0000100000000000000"
"0000100000000000000"
"0000001100000000000"
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
    gameTest.getClassicBoard().printBoard();
    EXPECT_EQ(gameTest.checkDoubleThree(4, 4, WHITE), false);
}
