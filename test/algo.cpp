#include "../inc/algorithm.hpp"
#include "../inc/gomoku.hpp"

#include <chrono>
#include <gtest/gtest.h>
#include <thread>

void fillGame(Game& gameBoard, std::string player1, std::string player2 = "")
{
    std::reverse(player1.begin(), player1.end());
    IBoard::bitboard board_p1(player1);

    std::reverse(player2.begin(), player2.end());
    IBoard::bitboard board_p2(player2);

    int width = gameBoard.getClassicBoard().getWidth();
    int size = board_p1.size();
    for (int i = 0; i < size; i++) {
        if (board_p1[i])
            gameBoard.setPosToBoards(i % width, i / width, 1);
        else if (int(board_p2.size()) > i && board_p2[i])
            gameBoard.setPosToBoards(i % width, i / width, 2);
    }
}

TEST(Algorithm, timesUp)
{
    int increment = 10;
    int sizeMs = TIME_UP + (2 * increment);

    int shouldBeTrue = sizeMs - (increment * 5);
    const timePoint start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < sizeMs; i += increment) {
        std::this_thread::sleep_for(std::chrono::milliseconds(increment));
        if (shouldBeTrue == i) {
            EXPECT_EQ(times_up(start), false);
        }
    }
    EXPECT_EQ(times_up(start), true);
}

TEST(MiniMaxUtils, surroundingBits)
{

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
        "0000000000000001000"
        "0000000000000000000"
        "0000000000000000000"
        "1000000000000000100");
    std::string str_test_surronded(
        "1111000000000011110"
        "1111000011111011110"
        "0111000111111100000"
        "0000000111111100000"
        "0000000111011100000"
        "0000000000000000000"
        "0000000000000000000"
        "0000000000000000000"
        "0000000000000000000"
        "0000000000000000000"
        "0000000000000000000"
        "0000000000000000000"
        "0000000000000000000"
        "0000000000000000000"
        "0000000000000011100"
        "0000000000000011100"
        "0000000000000011100"
        "1100000000000001110"
        "1100000000000001110");
    Game gameTest;
    fillGame(gameTest, str_test);

    std::reverse(str_test_surronded.begin(), str_test_surronded.end());
    IBoard::bitboard surrounded(str_test_surronded);

    auto bits = getSurroundingBits(gameTest);

    EXPECT_EQ(bits, surrounded);
}

TEST(MiniMaxUtils, surroundingBitsTwoPlayers)
{

    std::string str_p1(
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
        "0000000000000000000"
        "1000000000000000000");
    std::string str_p2(
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
        "1000000000000000000"
        "0100000000000000000");
    std::string str_waited(
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
        "1100000000000000000"
        "1110000000000000000"
        "1110000000000000000");
    Game gameTest;
    fillGame(gameTest, str_p1, str_p2);

    std::reverse(str_waited.begin(), str_waited.end());
    IBoard::bitboard surrounded(str_waited);

    auto bits = getSurroundingBits(gameTest);

    EXPECT_EQ(bits, surrounded);
}

TEST(MiniMaxUtils, generatePossibleMoves)
{

    std::string str_test(
        "0010000000000000000"
        "0010000000000000000"
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

    Game gameTest;
    int width = gameTest.getClassicBoard().getWidth();
    int size = test.size();
    for (int i = 0; i < size; i++) {
        if (!test[i])
            continue;
        gameTest.setPosToBoards(i % width, i / width, 1);
    }

    gameSet nextMoves = generatePossibleMoves(gameTest, 1, true, 0);
    int nb_moves = static_cast<int>(nextMoves.size());
    if (PRUNING < 7)
        EXPECT_EQ(nb_moves, PRUNING);
    else
        EXPECT_EQ(nb_moves, 7);
}

TEST(MiniMaxUtils, generatePossibleMovesCompare)
{

    std::string str_test_p1(
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
        "0000000000000000000"
        "1000000000000000000");
    std::string str_test_p2(
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
        "1000000000000000000"
        "0100000000000000000");

    std::reverse(str_test_p1.begin(), str_test_p1.end());
    IBoard::bitboard test_p1(str_test_p1);

    std::reverse(str_test_p2.begin(), str_test_p2.end());
    IBoard::bitboard test_p2(str_test_p2);

    Game gameTest;
    int width = gameTest.getClassicBoard().getWidth();
    int size = test_p1.size();
    for (int i = 0; i < size; i++) {
        if (test_p1[i])
            gameTest.setPosToBoards(i % width, i / width, 1);
        else if (test_p2[i])
            gameTest.setPosToBoards(i % width, i / width, 2);
    }

    gameSet nextMoves = generatePossibleMoves(gameTest, 1, true, 0);
    int nb_new_moves = nextMoves.size();
    if (PRUNING < 5)
        EXPECT_EQ(nb_new_moves, PRUNING);
    else
        EXPECT_EQ(nb_new_moves, 5);
}