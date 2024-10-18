#include "../inc/Game.hpp"
#include "../inc/ClassicBoard.hpp"
#include <algorithm>
#include <gtest/gtest.h>

TEST(extractPattern, Classic){
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

TEST(extractPattern, Transpose){
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

TEST(extractPattern, Diag){
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

TEST(extractPattern, AntiDiag){
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