#include "../inc/gomoku.hpp"
#include <gtest/gtest.h>

TEST(HandleMouse, TestOut) {
    EXPECT_EQ(handleMouse(MARGIN - 10, MARGIN - 10), false);
    EXPECT_EQ(handleMouse(-15, SCREEN_HEIGHT), false);
    EXPECT_EQ(handleMouse(-15, SCREEN_HEIGHT + 100), false);
    EXPECT_EQ(handleMouse(SCREEN_WIDTH + 1000, -100), false);
    EXPECT_EQ(handleMouse(SCREEN_WIDTH + 1, SCREEN_HEIGHT + 1), false);
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