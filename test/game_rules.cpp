#include "../inc/ClassicBoard.hpp"
#include "../inc/Game.hpp"
#include <algorithm>
#include <gtest/gtest.h>

TEST(BoardRules, doubleThree)
{
    std::string str_test(
        "0000000000000000000"
        "0010000000000000000"
        "0001000000000000000"
        "0000000000000000000"
        "0000000110000000000"
        "0000000000000000000"
        "0000000000000000000"
        "0000000000000000000"
        "0000000000000000000"
        "0000000000000000000"
        "0000000000000000000"
        "0000100000000000000"
        "0001000000000000000"
        "0000000000000000000"
        "0011000000000000000"
        "0000000000000000000"
        "0000000000000000000"
        "0000000000000000000"
        "0000000000000000000");
    std::reverse(str_test.begin(), str_test.end());
    IBoard::bitboard test(str_test);

    Game gameTest;
    int size = test.size();
    int width = gameTest.getClassicBoard().getWidth();
    for (int i = 0; i < size; i++) {
        if (!test[i])
            continue;
        gameTest.setPosToBoards(i % width, i / width, test[i]);
    }

    EXPECT_EQ(gameTest.isDoubleThree(5, 4, WHITE), true);
    gameTest.setPosToBoards(4, 4, BLACK);
    EXPECT_EQ(gameTest.isDoubleThree(5, 4, WHITE), false);

    EXPECT_EQ(gameTest.isDoubleThree(1, 14, WHITE), true);
    gameTest.setPosToBoards(4, 14, BLACK);
    EXPECT_EQ(gameTest.isDoubleThree(1, 14, WHITE), false);
}

TEST(BoardRules, Capture)
{
    const int dirX[8] = { 1, 0, 1, 1, -1, 0, -1, -1 };
    const int dirY[8] = { 0, 1, -1, 1, 0, -1, 1, -1 };

    std::string str_test(
        "0000000000000000000"
        "0020020020000000000"
        "0001010100000000000"
        "0000111000000000000"
        "0021101120000000000"
        "0000111000000000000"
        "0001010100000000000"
        "0020020020000000000"
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
    int size = str_test.size();
    int width = gameTest.getClassicBoard().getWidth();
    for (int i = 0; i < size; i++) {
        if (str_test[i] == '0')
            continue;
        gameTest.setPosToBoards(i % width, i / width, str_test[i] - 48);
    }

    int x = 5, y = 4;

    gameTest.setPosToBoards(x, y, BLACK);
    std::vector<uint16_t> capturesBoard = gameTest.isCapture(x, y, BLACK);
    EXPECT_EQ(capturesBoard.size(), static_cast<size_t>(8));

    for (int i = 0; i < 8; i++) {
        gameTest.removePosToBoards(x + dirX[i], y + dirY[i]);
        gameTest.removePosToBoards(x + dirX[i] * 2, y + dirY[i] * 2);

        EXPECT_EQ(gameTest.getClassicBoard().getPos(x + dirX[i], y + dirY[i]), EMPTY);
        EXPECT_EQ(gameTest.getClassicBoard().getPos(x + dirX[i] * 2, y + dirY[i] * 2), EMPTY);

        EXPECT_EQ(gameTest.getTransposedBoard().getPos(x + dirX[i], y + dirY[i]), EMPTY);
        EXPECT_EQ(gameTest.getTransposedBoard().getPos(x + dirX[i] * 2, y + dirY[i] * 2), EMPTY);

        EXPECT_EQ(gameTest.getDiagBoard().getPos(x + dirX[i], y + dirY[i]), EMPTY);
        EXPECT_EQ(gameTest.getDiagBoard().getPos(x + dirX[i] * 2, y + dirY[i] * 2), EMPTY);

        EXPECT_EQ(gameTest.getAntiDiagBoard().getPos(x + dirX[i], y + dirY[i]), EMPTY);
        EXPECT_EQ(gameTest.getAntiDiagBoard().getPos(x + dirX[i] * 2, y + dirY[i] * 2), EMPTY);
    }
}

TEST(BoardRules, CanCapture)
{
    std::string str_test(
        "0000000000000000000"
        "0000000000000000000"
        "0000000000000000000"
        "0011200100000000000"
        "0000001000000000000"
        "0000020000000000000"
        "0000000000000000000"
        "0000000000000000000"
        "0000000000000000000"
        "0000200000000000000"
        "0000020000000000000"
        "0000001000000000000"
        "0000000000000000000"
        "0000000000000000000"
        "0020000000000000000"
        "0200001000000000000"
        "1000001000000000000"
        "0000002000000000000"
        "0000000000000000000");

    Game gameTest;
    int size = str_test.size();
    int width = gameTest.getClassicBoard().getWidth();
    for (int i = 0; i < size; i++) {
        if (str_test[i] == '0')
            continue;
        gameTest.setPosToBoards(i % width, i / width, str_test[i] - 48);
    }

    EXPECT_EQ(gameTest.canCapture(1, 3, BLACK), true);
    EXPECT_EQ(gameTest.canCapture(1, 3, WHITE), false);

    EXPECT_EQ(gameTest.canCapture(8, 2, BLACK), true);
    EXPECT_EQ(gameTest.canCapture(8, 2, WHITE), false);

    EXPECT_EQ(gameTest.canCapture(3, 8, WHITE), true);
    EXPECT_EQ(gameTest.canCapture(3, 8, BLACK), false);

    EXPECT_EQ(gameTest.canCapture(3, 13, WHITE), true);
    EXPECT_EQ(gameTest.canCapture(3, 13, BLACK), false);

    EXPECT_EQ(gameTest.canCapture(6, 14, BLACK), true);
    EXPECT_EQ(gameTest.canCapture(6, 14, WHITE), false);
}

TEST(BoardRules, Win)
{
    {
        std::string str_test(
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000001000000000000"
            "0000000100000000000"
            "0000000010000000000"
            "0000000000000000000"
            "0000000000100000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000200000000000000"
            "0000020000000000000"
            "0000002000000000000"
            "0000000200000000000"
            "0000000020000000000"
            "0000000000000000000");

        Game gameTest;
        int size = str_test.size();
        int width = gameTest.getClassicBoard().getWidth();
        for (int i = 0; i < size; i++) {
            if (str_test[i] == '0')
                continue;
            gameTest.setPosToBoards(i % width, i / width, str_test[i] - 48);
        }

        EXPECT_EQ(gameTest.playerWin(WHITE), false);
        EXPECT_EQ(gameTest.playerWin(BLACK), true);
    }
    {
        std::string str_test(
            "0000000001000000000"
            "0000000010000000000"
            "0000000100000000000"
            "0000001000000000000"
            "0000010020000000000"
            "0000000200000000000"
            "0000000000000000000"
            "0000020000000000000"
            "0000200000000000000"
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
        int size = str_test.size();
        int width = gameTest.getClassicBoard().getWidth();
        for (int i = 0; i < size; i++) {
            if (str_test[i] == '0')
                continue;
            gameTest.setPosToBoards(i % width, i / width, str_test[i] - 48);
        }

        EXPECT_EQ(gameTest.playerWin(WHITE), true);
        EXPECT_EQ(gameTest.playerWin(BLACK), false);
    }
    {
        std::string str_test(
            "0000000000000000000"
            "0000000000000000000"
            "0000000001000000000"
            "0000000001000000000"
            "0000000001000000000"
            "0000000001000000000"
            "0000000001000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000200000000000"
            "0000000200000000000"
            "0000000200000000000"
            "0000000000000000000"
            "0000000200000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000");

        Game gameTest;
        int size = str_test.size();
        int width = gameTest.getClassicBoard().getWidth();
        for (int i = 0; i < size; i++) {
            if (str_test[i] == '0')
                continue;
            gameTest.setPosToBoards(i % width, i / width, str_test[i] - 48);
        }

        EXPECT_EQ(gameTest.playerWin(WHITE), true);
        EXPECT_EQ(gameTest.playerWin(BLACK), false);
    }
    {
        std::string str_test(
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000001111100000000"
            "0000000000000000000"
            "0000000000000000000"
            "0222200000000000000"
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
        int size = str_test.size();
        int width = gameTest.getClassicBoard().getWidth();
        for (int i = 0; i < size; i++) {
            if (str_test[i] == '0')
                continue;
            gameTest.setPosToBoards(i % width, i / width, str_test[i] - 48);
        }

        EXPECT_EQ(gameTest.playerWin(WHITE), true);
        EXPECT_EQ(gameTest.playerWin(BLACK), false);
    }
}

TEST(BoardRules, EndCapture)
{
    {
        std::string str_test(
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000001000000000000"
            "0000000100000000000"
            "0000000010000000000"
            "0000000021100000000"
            "0000000000100000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000200000000000000"
            "0000020000000000000"
            "0000002000000000000"
            "0000002200000000000"
            "0000001020000000000"
            "0000000000000000000");

        Game gameTest;
        int size = str_test.size();
        int width = gameTest.getClassicBoard().getWidth();
        for (int i = 0; i < size; i++) {
            if (str_test[i] == '0')
                continue;
            gameTest.setPosToBoards(i % width, i / width, str_test[i] - 48);
        }

        EXPECT_EQ(gameTest.playerWin(WHITE), false);
        EXPECT_EQ(gameTest.playerWin(BLACK), false);
    }
    {
        std::string str_test(
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000001000000000000"
            "0000000110000000000"
            "0000000010000000000"
            "0000000021000000000"
            "0000000000100000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000020000000000"
            "0000222220000000000"
            "0000001000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000");

        Game gameTest;
        int size = str_test.size();
        int width = gameTest.getClassicBoard().getWidth();
        for (int i = 0; i < size; i++) {
            if (str_test[i] == '0')
                continue;
            gameTest.setPosToBoards(i % width, i / width, str_test[i] - 48);
        }

        EXPECT_EQ(gameTest.playerWin(WHITE), false);
        EXPECT_EQ(gameTest.playerWin(BLACK), false);
    }
    {
        std::string str_test(
            "0000000001000000000"
            "0000002010000000000"
            "0000000100000000000"
            "0000001010000000000"
            "0000010020000000000"
            "0000000220000000000"
            "0000002000000000000"
            "0000020000000000000"
            "0000200000000000000"
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
        int size = str_test.size();
        int width = gameTest.getClassicBoard().getWidth();
        for (int i = 0; i < size; i++) {
            if (str_test[i] == '0')
                continue;
            gameTest.setPosToBoards(i % width, i / width, str_test[i] - 48);
        }

        EXPECT_EQ(gameTest.playerWin(WHITE), false);
        EXPECT_EQ(gameTest.playerWin(BLACK), false);
    }
    {
        std::string str_test(
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000020000000"
            "0000000000200000000"
            "0000000002000000000"
            "0000000020010000000"
            "0000000201100000000"
            "0000000001000000000"
            "0000000000020000000"
            "0000000000000000000"
            "0000000100000000000"
            "0000000010000000000"
            "0000000001000000000"
            "0000000000100000000"
            "0000000000010000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000");

        Game gameTest;
        int size = str_test.size();
        int width = gameTest.getClassicBoard().getWidth();
        for (int i = 0; i < size; i++) {
            if (str_test[i] == '0')
                continue;
            gameTest.setPosToBoards(i % width, i / width, str_test[i] - 48);
        }

        EXPECT_EQ(gameTest.playerWin(WHITE), true);
        EXPECT_EQ(gameTest.playerWin(BLACK), true);
    }
    {
        std::string str_test(
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000200000"
            "0000000000000012000"
            "0000000000000010000"
            "0000000000000010000"
            "0000000000000210000"
            "0000000000000012000"
            "0000000000000200000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000");

        Game gameTest;
        int size = str_test.size();
        int width = gameTest.getClassicBoard().getWidth();
        for (int i = 0; i < size; i++) {
            if (str_test[i] == '0')
                continue;
            gameTest.setPosToBoards(i % width, i / width, str_test[i] - 48);
        }

        EXPECT_EQ(gameTest.playerWin(WHITE), true);
    }
    {
        std::string str_test(
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000001000000000"
            "0000000112000010000"
            "0000000002000200000"
            "0000001222010100000"
            "0000000002111200000"
            "0000000002201000000"
            "0001000001010000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000"
            "0000000000000000000");

        Game gameTest;
        int size = str_test.size();
        int width = gameTest.getClassicBoard().getWidth();
        for (int i = 0; i < size; i++) {
            if (str_test[i] == '0')
                continue;
            gameTest.setPosToBoards(i % width, i / width, str_test[i] - 48);
        }

        EXPECT_EQ(gameTest.playerWin(BLACK), true);
    }
    {
        std::string str_test(
            "0000000000000000000"
            "0000000000000000000"
            "0000100000000200000"
            "0000100000002000000"
            "0000100000020000000"
            "0000100000200000000"
            "0000100002000000000"
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
        int size = str_test.size();
        int width = gameTest.getClassicBoard().getWidth();
        for (int i = 0; i < size; i++) {
            if (str_test[i] == '0')
                continue;
            gameTest.setPosToBoards(i % width, i / width, str_test[i] - 48);
        }

        EXPECT_EQ(gameTest.inFiveAtPos(9, 6, BLACK), true);
    }
}
