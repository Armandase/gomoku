#include "../inc/gomoku.hpp"
#include <gtest/gtest.h>

TEST(HandleMouse, TestOut) {
    EXPECT_EQ(handleMouse(-15, SCREEN_HEIGHT), false);
    EXPECT_EQ(handleMouse(-15, SCREEN_HEIGHT + 100), false);
    EXPECT_EQ(handleMouse(SCREEN_WIDTH + 1000, -100), false);
    EXPECT_EQ(handleMouse(SCREEN_WIDTH + 1, SCREEN_HEIGHT + 1), false);
}

TEST(HandleMouse, TestIn) {
    EXPECT_EQ(handleMouse(0, 0), true);
    EXPECT_EQ(handleMouse(0, SCREEN_HEIGHT), true);
    EXPECT_EQ(handleMouse(SCREEN_WIDTH, 0), true);
    EXPECT_EQ(handleMouse(SCREEN_WIDTH, SCREEN_HEIGHT), true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}