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
#define DEPTH 10
#define PRUNING 3
#define PATTERN_SIZE 5
#define MERGE_SIZE (PATTERN_SIZE * 2 - 1)
#define TIME_UP 450
#define FONT_SIZE 24

enum side {
    LEFT,
    RIGHT,
};

enum player {
    EMPTY = 0,
    WHITE,
    BLACK,
    ADVISOR,
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

// const std::array<const t_pattern, 23> patternsArray { {
//     // USELESS PATTERNS - Minimal value as they don't directly influence the game
//     { patternMerge("000011110"), patternMerge("000100001"), 6, 0 },
//     { patternMerge("000001110"), patternMerge("000010001"), 5, 0 },
//     { patternMerge("000000110"), patternMerge("000001001"), 4, 0 },

//     // WINNING CONDITION - Five in a row
//     { patternMerge("000011111"), patternMerge("000000000"), 5, 100000000 }, // FIVE (unblockable win)
//     { patternMerge("000010000"), patternMerge("000001111"), 5, 100000000 },
//     { patternMerge("000000001"), patternMerge("000011110"), 5, 100000000 },

//     // STRONG THREATS - Open Four (either side open)
//     { patternMerge("000011110"), patternMerge("000000000"), 6, 10000000 }, // FOUR (open on both ends)

//     // MODERATE THREATS - One-Sided Open Four
//     { patternMerge("000000001"), patternMerge("000001110"), 4, 1000000 },
//     { patternMerge("000001000"), patternMerge("000000111"), 4, 1000000 },

//     { patternMerge("000001111"), patternMerge("000000000"), 4, 1000000 }, // FOUR
//     { patternMerge("000011011"), patternMerge("000000000"), 5, 1000000 }, // FOUR
//     { patternMerge("000010111"), patternMerge("000000000"), 5, 1000000 }, // FOUR
//     { patternMerge("000011101"), patternMerge("000000000"), 5, 1000000 }, // FOUR

//     // POTENTIAL BUILD-UP - Open Three
//     { patternMerge("000001110"), patternMerge("000000000"), 5, 100000 }, // THREE (open on both ends)
//     { patternMerge("000000111"), patternMerge("000000000"), 3, 10000 }, // THREE

//     // MODERATE THREATS
//     { patternMerge("000001101"), patternMerge("000000000"), 4, 1000 },
//     { patternMerge("000001011"), patternMerge("000000000"), 4, 1000 },

//     // MODERATE OPPORTUNITIES - Defensive or transitional patterns
//     { patternMerge("000001001"), patternMerge("000000110"), 4, 100 }, // Capture opportunity

//     // LOW-PRIORITY OPPORTUNITIES - Transitional steps
//     { patternMerge("000000110"), patternMerge("000000000"), 4, 50 }, // OPEN TWO
//     { patternMerge("000000011"), patternMerge("000000000"), 2, 10 }, // TWO

//     // FILLERS - Low-value potential plays
//     { patternMerge("000000101"), patternMerge("000000000"), 3, 5 },
//     { patternMerge("000001010"), patternMerge("000000000"), 4, 5 },
//     { patternMerge("000001001"), patternMerge("000000000"), 4, 5 },
// }};

const std::array<const t_pattern, 37> patternsArray { {
    // USELESS PATTERNS - Minimal value as they don't directly influence the game
    { patternMerge("000011110"), patternMerge("000100001"), 6, 0 },
    { patternMerge("000001110"), patternMerge("000010001"), 5, 0 },
    { patternMerge("000000110"), patternMerge("000001001"), 4, 0 },

    // WINNING CONDITION - Five in a row                       2147483647
    { patternMerge("000011111"), patternMerge("000000000"), 5, 100000000 }, // FIVE (unblockable win)

    // DEFENSE FOUR
    { patternMerge("000010000"), patternMerge("000001111"), 5, 10000000 }, // FOUR
    { patternMerge("000000001"), patternMerge("000011110"), 5, 10000000 }, // FOUR
    { patternMerge("000000100"), patternMerge("000011011"), 5, 10000000 }, // FOUR
    { patternMerge("000001000"), patternMerge("000010111"), 5, 10000000 }, // FOUR
    { patternMerge("000000010"), patternMerge("000011101"), 5, 10000000 },

    // STRONG THREATS - Open Four (either side open)
    { patternMerge("000011110"), patternMerge("000000000"), 6, 1000000 }, // FOUR (open on both ends)

    // MODERATE THREATS - One-Sided Open Four
    { patternMerge("000001111"), patternMerge("000000000"), 4, 1000000 }, // FOUR
    { patternMerge("000011011"), patternMerge("000000000"), 5, 1000000 }, // FOUR
    { patternMerge("000010111"), patternMerge("000000000"), 5, 1000000 }, // FOUR
    { patternMerge("000011101"), patternMerge("000000000"), 5, 1000000 }, // FOUR

    // DENFENSE THREE
    { patternMerge("000001000"), patternMerge("000000111"), 4, 100000 }, // THREE
    { patternMerge("000000001"), patternMerge("000001110"), 4, 100000 }, // THREE
    // POTENTIAL BUILD-UP - Open Three
    { patternMerge("000001110"), patternMerge("000000000"), 5, 10000 }, // THREE (open on both ends)
    { patternMerge("000001110"), patternMerge("000000000"), 4, 10000 }, // THREE
    { patternMerge("000000111"), patternMerge("000000000"), 3, 10000 }, // THREE

    // MODERATE THREATS
    { patternMerge("000001101"), patternMerge("000000000"), 4, 5000 },
    { patternMerge("000000010"), patternMerge("000001101"), 4, 5000 },
    { patternMerge("000001011"), patternMerge("000000000"), 4, 5000 },
    { patternMerge("000000100"), patternMerge("000001011"), 4, 5000 },
    { patternMerge("000001110"), patternMerge("000000001"), 4, 5000 },
    { patternMerge("000000111"), patternMerge("000001000"), 4, 5000 },

    // MODERATE OPPORTUNITIES - Defensive or transitional patterns
    { patternMerge("000001001"), patternMerge("000000110"), 4, 1000 }, // Capture opportunity

    // LOW-PRIORITY OPPORTUNITIES - Transitional steps
    { patternMerge("000000110"), patternMerge("000000000"), 4, 500 }, // OPEN TWO
    { patternMerge("000000001"), patternMerge("000000110"), 3, 500 }, // OPEN TWO
    { patternMerge("000000011"), patternMerge("000000000"), 3, 100 }, // TWO
    { patternMerge("000000110"), patternMerge("000000000"), 3, 100 }, // TWO
    { patternMerge("000000011"), patternMerge("000000000"), 2, 100 }, // TWO
    { patternMerge("000000100"), patternMerge("000000011"), 3, 100 }, // TWO

    // FILLERS - Low-value potential plays
    { patternMerge("000000101"), patternMerge("000000000"), 3, 50 },
    { patternMerge("000001010"), patternMerge("000000000"), 4, 50 },
    { patternMerge("000001001"), patternMerge("000000000"), 4, 50 },
} };

int intlen(int number);
int coordToBoard(int coor);
int boardToRender(int value);
bool handleMouse(int mouseX, int mouseY);
int modeSelection(Game& game, Render& render, Button& player, Button& IA);
void place_stone(Game& board, Render& render, int x, int y, int& player, bool& endgame);
void placeAdvisorStone(int x, int y, Render& render);
bool posValid(Game& game, int x, int y, int player, bool verbose = false);
void resetGame(Game& game, Render& render, int player);

#endif