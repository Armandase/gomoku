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

    Game board;

    int size = test.size();
    int width = board.getClassicBoard().getWidth();
    for (int i = 0; i < size; i++){
        if (!test[i])
            continue;
        board.setPosToBoards(i % width, i / width, test[i]);
    }
    
    {
        patternBitset  waitedResult("1101");

        EXPECT_EQ(board.getClassicBoard().extractPattern(1, 1, 4, 1), waitedResult);
    }
    {
        patternBitset  waitedResult("0110");

        EXPECT_EQ(board.getClassicBoard().extractPatternReversed(5, 1, 4, 1), waitedResult);
    }

    {
        patternBitset  waitedResult("0000");
        EXPECT_EQ(board.getClassicBoard().extractPattern(width-3, 1, 4, 1), waitedResult);
    }

    {
        patternBitset  waitedResult("0001");
        EXPECT_EQ(board.getClassicBoard().extractPattern(width-2, 1, 1, 1), waitedResult);
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

    Game board;

    int size = test.size();
    int width = board.getTransposedBoard().getWidth();
    for (int i = 0; i < size; i++){
        if (!test[i])
            continue;
        board.setPosToBoards(i % width, i / width, test[i]);
    }
    
    {
        patternBitset  waitedResult("0111");

        EXPECT_EQ(board.getTransposedBoard().extractPattern(1, 1, 4, 1), waitedResult);
    }

    // REVERSE
    {
        patternBitset  waitedResult("0111");

        EXPECT_EQ(board.getTransposedBoard().extractPatternReversed(1, 4, 4, 1), waitedResult);
    }
}

TEST(DiagBoardTest, extractPattern){
    std::string str_test(
"0000000000000000000"
"0101100000000000000"
"0100000000000000000"
"0101000000000000000"
"0000100000000000000"
"0001000000000000000"
"0010000000000000000"
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
"0000000000000000000");
    std::reverse(str_test.begin(), str_test.end());
    IBoard::bitboard test(str_test);

    Game board;

    int size = test.size();
    int width = board.getDiagBoard().getWidth();
    for (int i = 0; i < size; i++){
        if (!test[i])
            continue;
        board.setPosToBoards(i % width, i / width, test[i]);
    }
    {
        patternBitset  waitedResult("0000");
        //Doit etre null car l'extraction est trop grande par rapport aux coordonnes (ca sort du plateau)
        EXPECT_EQ(board.getDiagBoard().extractPattern(1, 1, 4, 1), waitedResult);
    }
    {
        patternBitset  waitedResult("0010");
        EXPECT_EQ(board.getDiagBoard().extractPattern(0, 3, 4, 1), waitedResult);
    }
    {
        patternBitset  waitedResult("1111");
        EXPECT_EQ(board.getDiagBoard().extractPattern(1, 7, 4, 1), waitedResult);
    }

    // REVERSE
    {
        patternBitset  waitedResult("0000");
        //Doit etre null car l'extraction est trop grande par rapport aux coordonnes (ca sort du plateau)
        EXPECT_EQ(board.getDiagBoard().extractPatternReversed(1, 5, 4, 1), waitedResult);
    }
    {
        patternBitset  waitedResult("1010");
        EXPECT_EQ(board.getDiagBoard().extractPatternReversed(3, 1, 4, 1), waitedResult);
    }
    {
        patternBitset  waitedResult("1010");
        EXPECT_EQ(board.getDiagBoard().extractPatternReversed(3, 1, 4, 1), waitedResult);
    }
    {
        patternBitset  waitedResult("0111");
        EXPECT_EQ(board.getDiagBoard().extractPatternReversed(5, 3, 4, 1), waitedResult);
    }
}

TEST(AntiDiagBoardTest, extractPattern){
    std::string str_test(
"0000000000000000000"
"0101100000000000000"
"0100000000000000000"
"0101000000000000000"
"0000100000000000000"
"0001000000000000000"
"0000100000000000000"
"0000010000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0001000000000000000"
"0000100000000000000"
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
        EXPECT_EQ(board.extractPattern(1, 16, 4, 1), waitedResult);
    }
    {
        patternBitset  waitedResult("0011");
        EXPECT_EQ(board.extractPattern(3, 15, 4, 1), waitedResult);
    }
    {
        patternBitset  waitedResult("1110");
        EXPECT_EQ(board.extractPattern(2, 4, 4, 1), waitedResult);
    }
    {
        patternBitset  waitedResult("1101");
        EXPECT_EQ(board.extractPattern(1, 1, 4, 1), waitedResult);
    }

    // REVERSE
    {
        patternBitset  waitedResult("0000");
        //Doit etre null car l'extraction est trop grande par rapport aux coordonnes (ca sort du plateau)
        EXPECT_EQ(board.extractPatternReversed(2, 3, 4, 1), waitedResult);
    }
    {
        patternBitset  waitedResult("1100");
        EXPECT_EQ(board.extractPatternReversed(4, 16, 4, 1), waitedResult);
    }
}

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
    EXPECT_EQ(gameTest.checkDoubleThree(4, 4, WHITE), true);
    
}
