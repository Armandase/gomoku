#include "../inc/algorithm.hpp"
#include "../inc/gomoku.hpp"
#include "../inc/TranspositionTable.hpp"

# include <thread>
# include <chrono>
# include <gtest/gtest.h>


TEST(Algorithm, timesUp) {
    int increment = 10;
    int sizeMs = TIME_UP + (2 * increment);

    int shouldBeTrue = sizeMs - (increment * 5);
    const timePoint start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < sizeMs; i+=increment){
        std::this_thread::sleep_for(std::chrono::milliseconds(increment));
        if (shouldBeTrue == i){
            EXPECT_EQ(times_up(start), false);
        }
    }
    EXPECT_EQ(times_up(start), true);
}

TEST(TranspositionTable, store){

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
    int width = gameTest.getDiagBoard().getWidth();
    int size = test.size(); 
    for (int i = 0; i < size; i++){
        if (!test[i])
            continue;
        gameTest.setPosToBoards(i % width, i / width, 1);
    }
    
    TranspositionTable table;
    size_t cmp = 1;
    table.store(gameTest, 10);
    EXPECT_EQ(table.getTable().size(), cmp);
    table.store(gameTest, 10);
    EXPECT_EQ(table.getTable().size(), cmp);

    cmp = 2;
    gameTest.setPosToBoards(width - 1, width - 1, cmp);
    table.store(gameTest, 10);
    EXPECT_EQ(table.getTable().size(), cmp);
    // EXPECT_EQ(gameTest.getAntiDiagBoard().getPlayer1(), waited_result);
}

TEST(MiniMaxUtils, surroundingBits){

    std::string str_test(
"1010000000000001100"
"0010000000000000000"
"0000000001010000000"
"0000000010001000000"
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

    Game gameTest;
    int width = gameTest.getDiagBoard().getWidth();
    int size = test.size(); 
    for (int i = 0; i < size; i++){
        if (!test[i])
            continue;
        gameTest.setPosToBoards(i % width, i / width, 1);
    }
    
    // std::cout << "Classic :"<< gameTest.getClassicBoard().getPlayer1() << std::endl;
    auto bits = getSurroundingBits(gameTest);
    // std::cout << "Bits :"<< bits << std::endl;

    for (int i = 0; i < NB_PLACEMENTS; ++i) {
        int x = i % (BOARD_SIZE + 1);
        int y = i / (BOARD_SIZE + 1);
        if (gameTest.getClassicBoard().getPos(x, y) && bits[i]) {
            // success to found a neighbour
            continue;
        }
    }
    int x = 2;
    int y = 0;
    EXPECT_EQ(bits[x + y * width] && gameTest.getClassicBoard().getPos(x, y), true);
    y = 1;
    EXPECT_EQ(bits[x + y * width] && gameTest.getClassicBoard().getPos(x, y), true);
    y = 2;
    EXPECT_EQ(bits[x + y * width] && gameTest.getClassicBoard().getPos(x, y), false);
}