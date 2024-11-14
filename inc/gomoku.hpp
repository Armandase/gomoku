#ifndef __GOMOKU_HPP__
#define __GOMOKU_HPP__

#include <array>
#include <bitset>
#include <climits>
#include <exception>
#include <iostream>
#include <set>
#include <vector>

#include "Button.hpp"
#include "Render.hpp"

#define GRID_SIZE 50
#define MARGIN 40
#define OFFSET (MARGIN * 6)
#define BOARD_SIZE 19
#define NB_PLACEMENTS (BOARD_SIZE * BOARD_SIZE)
#define BOARD_DIMENSIONS (GRID_SIZE * (BOARD_SIZE - 1))
#define SCREEN_HEIGHT (BOARD_DIMENSIONS + (2 * (MARGIN)))
#define SCREEN_WIDTH (BOARD_DIMENSIONS + MARGIN + OFFSET)
#define RADIUS (GRID_SIZE / 3)
#define DIAMETER (RADIUS * 2)
#define DEPTH 2
#define PRUNING 10
#define PATTERN_SIZE 5
#define MERGE_SIZE (PATTERN_SIZE * 2 - 1)
#define TIME_UP 500
#define FONT_SIZE 24

// extern const int8_t g_dirX[8] = { 0, 0, 1, -1, 1, -1, 1, -1};
// extern const int8_t g_dirY[8] = { 1, -1, 0, 0, 1, -1, -1, 1};

enum side {
    LEFT,
    RIGHT,
};

enum player {
    EMPTY = 0,
    WHITE,
    BLACK,
};

enum mode {
    PLAYER_MODE = 1,
    IA_MODE,
};

class Game;
class Button;
class Render;

typedef std::bitset<PATTERN_SIZE> patternBitset;
typedef std::bitset<MERGE_SIZE> patternMerge;

typedef struct s_pattern {
    const patternMerge player;
    const patternMerge opponent;
    const int length;
    const int value;
} t_pattern;

const std::array<const t_pattern, 19> patternsArray { {
    // USELESS PATTERNS
    { patternMerge("000011110"), patternMerge("000100001"), 6, 0 },
    { patternMerge("000001110"), patternMerge("000010001"), 5, 0 },
    { patternMerge("000000110"), patternMerge("000001001"), 4, 0 },
    // PATTERN SORT BY VALUE
    { patternMerge("000001111"), patternMerge("000000000"), 5, 10000000 }, // ONE SIDE OPEN FOUR
    { patternMerge("000011110"), patternMerge("000000000"), 5, 10000000 }, // ONE SIDE OPEN FOUR
    { patternMerge("000001101"), patternMerge("000000000"), 4, 100000 },
    { patternMerge("000001011"), patternMerge("000000000"), 4, 100000 },
    { patternMerge("000001110"), patternMerge("000000000"), 5, 100000 }, // OPEN THREE
    { patternMerge("000000111"), patternMerge("000000000"), 3, 10000 }, // THREE
    { patternMerge("000001001"), patternMerge("000000110"), 4, 10000 }, // CAPTURE
    { patternMerge("000001110"), patternMerge("000000001"), 5, 1000 }, // ONE SIDE OPEN THREE
    { patternMerge("000001110"), patternMerge("000010000"), 5, 1000 }, // ONE SIDE OPEN THREE
    { patternMerge("000000110"), patternMerge("000000000"), 4, 1000 }, // OPEN TWO
    { patternMerge("000000011"), patternMerge("000000000"), 2, 100 }, // TWO
    { patternMerge("000000101"), patternMerge("000000000"), 3, 10 },
    { patternMerge("000001010"), patternMerge("000000000"), 4, 10 },
    { patternMerge("000001001"), patternMerge("000000000"), 4, 10 },
} };

// const std::array<const t_pattern, 11> patternsArray { {
//     // SIZE 4
//     { patternMerge("000001111"), patternMerge("000000000"), 4, 1000000 },
//     { patternMerge("000001101"), patternMerge("000000000"), 4, 100000 },
//     { patternMerge("000001011"), patternMerge("000000000"), 4, 100000 },
//     { patternMerge("000001110"), patternMerge("000000001"), 4, 1000 },
//     { patternMerge("000000111"), patternMerge("000001000"), 4, 1000 },
//     { patternMerge("000001001"), patternMerge("000000110"), 4, 10000 },
//     { patternMerge("000001001"), patternMerge("000000000"), 4, 10 },
//     { patternMerge("000001010"), patternMerge("000000000"), 4, 10 },
//     // SIZE 3
//     { patternMerge("000000111"), patternMerge("000000000"), 3, 10000 },
//     { patternMerge("000000101"), patternMerge("000000000"), 3, 10 },
//     // SIZE 2
//     { patternMerge("000000011"), patternMerge("000000000"), 2, 100 },
// } };
bool handleMouse(int mouseX, int mouseY);
int modeSelection(Game& game, Render& render, Button& player, Button& IA);
void place_stone(Game& board, Render& render, int x, int y, int& player);
bool posValid(Game& game, int x, int y, int player);

#endif