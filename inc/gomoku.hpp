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
#define TIME_UP 470
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
    IA_VS_IA,
    PVP_PRO,
    PVP_LONGPRO,
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

const std::array<const t_pattern, 65> patternsArray { {
    // USELESS PATTERNS - Minimal value as they don't directly influence the game
    { patternMerge("000011110"), patternMerge("000100001"), 6, -200 },
    { patternMerge("000001110"), patternMerge("000100001"), 6, -200 },
    { patternMerge("000011100"), patternMerge("000100001"), 6, -200 },
    { patternMerge("000000110"), patternMerge("000100001"), 6, -200 },
    { patternMerge("000011000"), patternMerge("000100001"), 6, -200 },
    { patternMerge("000001100"), patternMerge("000100001"), 6, -200 },
    { patternMerge("000001110"), patternMerge("000010001"), 5, -200 },
    { patternMerge("000000110"), patternMerge("000010001"), 5, -200 },
    { patternMerge("000001100"), patternMerge("000010001"), 5, -200 },
    { patternMerge("000000110"), patternMerge("000001001"), 4, -200 },
    { patternMerge("000000010"), patternMerge("000001001"), 4, -200 },
    { patternMerge("000000100"), patternMerge("000001001"), 4, -200 },

    // WINNING CONDITION - Five in a row                       2147483647
    { patternMerge("000011111"), patternMerge("000000000"), 5, 100000000 }, // FIVE

    // DEFENSE FOUR
    { patternMerge("000100000"), patternMerge("000001111"), 6, 9000000 }, // FOUR
    { patternMerge("000100000"), patternMerge("000011110"), 6, 9000000 }, // FOUR
    { patternMerge("000000001"), patternMerge("000011110"), 6, 9000000 }, // FOUR
    { patternMerge("000000001"), patternMerge("000111100"), 6, 9000000 }, // FOUR
    { patternMerge("000000001"), patternMerge("000011110"), 5, 5000000 }, // FOUR
    { patternMerge("000000010"), patternMerge("000011101"), 5, 1000000 },
    { patternMerge("000000100"), patternMerge("000011011"), 5, 1000000 }, // FOUR
    { patternMerge("000001000"), patternMerge("000010111"), 5, 1000000 }, // FOUR
    { patternMerge("000010000"), patternMerge("000001111"), 5, 1000000 }, // FOUR

    // STRONG THREATS - Open Four (either side open)
    { patternMerge("000011110"), patternMerge("000000000"), 6, 1000000 }, // FOUR (open on both ends)

    // MODERATE THREATS
    { patternMerge("000001111"), patternMerge("000000000"), 5, 100000 }, // FOUR
    { patternMerge("000011110"), patternMerge("000000000"), 5, 100000 }, // FOUR
    { patternMerge("000011011"), patternMerge("000000000"), 5, 100000 }, // FOUR
    { patternMerge("000010111"), patternMerge("000000000"), 5, 100000 }, // FOUR
    { patternMerge("000011101"), patternMerge("000000000"), 5, 100000 }, // FOUR

    // DENFENSE THREE
    { patternMerge("000001000"), patternMerge("000000111"), 4, 90000 }, // THREE
    { patternMerge("000000001"), patternMerge("000001110"), 4, 90000 }, // THREE
    { patternMerge("000000010"), patternMerge("000001101"), 4, 30000 },
    { patternMerge("000000100"), patternMerge("000001011"), 4, 30000 },

    // POTENTIAL BUILD-UP - Open Three
    { patternMerge("000001001"), patternMerge("000000110"), 4, 90000 }, // Capture opportunity
    { patternMerge("000001110"), patternMerge("000000000"), 5, 10000 }, // THREE (open on both ends)
    { patternMerge("000000111"), patternMerge("000000000"), 5, 10000 }, // THREE (open on both ends)
    { patternMerge("000011100"), patternMerge("000000000"), 5, 10000 }, // THREE (open on both ends)
    { patternMerge("000011010"), patternMerge("000000000"), 5, 7000 }, // THREE (open on both ends)
    { patternMerge("000001011"), patternMerge("000000000"), 5, 7000 }, // THREE (open on both ends)
    { patternMerge("000010011"), patternMerge("000000000"), 5, 5000 }, // THREE (open on both ends)
    { patternMerge("000011001"), patternMerge("000000000"), 5, 5000 }, // THREE (open on both ends)
    { patternMerge("000001110"), patternMerge("000000001"), 4, 5000 }, // Cancel Capture
    { patternMerge("000000111"), patternMerge("000001000"), 4, 5000 }, // Cancel Capture

    // DEFENSE TWO
    { patternMerge("000000001"), patternMerge("000001010"), 4, 5000 },
    { patternMerge("000000100"), patternMerge("000001010"), 4, 5000 },
    { patternMerge("000000001"), patternMerge("000000110"), 4, 5000 },
    { patternMerge("000001000"), patternMerge("000000110"), 4, 5000 },
    { patternMerge("000001000"), patternMerge("000000101"), 4, 5000 },
    { patternMerge("000000010"), patternMerge("000000101"), 4, 5000 },

    // MODERATE THREATS
    { patternMerge("000001101"), patternMerge("000000000"), 4, 1000 },
    { patternMerge("000001011"), patternMerge("000000000"), 4, 1000 },

    // LOW-PRIORITY OPPORTUNITIES - Transitional steps
    { patternMerge("000001010"), patternMerge("000000000"), 4, 500 }, // OPEN TWO
    { patternMerge("000000110"), patternMerge("000000000"), 4, 500 }, // OPEN TWO
    { patternMerge("000000011"), patternMerge("000000000"), 4, 500 }, // OPEN TWO
    { patternMerge("000000101"), patternMerge("000000000"), 4, 500 }, // OPEN TWO

    { patternMerge("000000110"), patternMerge("000000000"), 4, 500 }, // OPEN TWO
    { patternMerge("000001000"), patternMerge("000000011"), 4, 500 }, // DEFEND EXTENDED TWO
    { patternMerge("000000001"), patternMerge("000001100"), 4, 500 }, // DEFEND EXTENDED TWO
    { patternMerge("000000100"), patternMerge("000000011"), 3, 500 }, // DEFEND TWO
    { patternMerge("000000001"), patternMerge("000000110"), 3, 500 }, // DEFEND TWO
    { patternMerge("000000110"), patternMerge("000000000"), 3, 250 }, // ONE SIDE TWO
    { patternMerge("000000011"), patternMerge("000000000"), 3, 250 }, // ONE SIDE TWO

    // FILLERS - Low-value potential plays
    { patternMerge("000000011"), patternMerge("000000000"), 2, 200 },
    { patternMerge("000000101"), patternMerge("000000000"), 3, 50 },
    { patternMerge("000001010"), patternMerge("000000000"), 4, 50 },
    { patternMerge("000001001"), patternMerge("000000000"), 4, 50 },

    // { patternMerge("000000001"), patternMerge("000000000"), 1, 5 },
} };

int intlen(int number);
int coordToBoard(int coor);
int boardToRender(int value);
bool handleMouse(int mouseX, int mouseY);
int modeSelection(Game& game, Render& render, Button& player, Button& IA, Button& IAvsIA, Button& PvPPro, Button& PvPSwap);
void place_stone(Game& board, Render& render, int x, int y, int& player, bool& endgame);
void placeAdvisorStone(int x, int y, Render& render);
bool posValid(Game& game, int x, int y, int player, bool verbose = false);
void resetGame(Game& game, Render& render);
void placeForbiddenMove(Game& game, Render& render, int player);

#endif