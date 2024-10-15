#include "../inc/gomoku.hpp"
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}