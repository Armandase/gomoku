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
#define OFFSET (MARGIN + 200)
#define BOARD_SIZE 18
#define NB_PLACEMENTS 361
#define BOARD_DIMENSIONS (GRID_SIZE * BOARD_SIZE)
#define SCREEN_HEIGHT (BOARD_DIMENSIONS + (2 * (MARGIN)))
#define SCREEN_WIDTH (BOARD_DIMENSIONS + MARGIN + OFFSET)
#define RADIUS (GRID_SIZE / 3)
#define DIAMETER (RADIUS * 2)
#define DEPTH 1
#define PRUNING 10
#define PARTTERN_SIZE 5
#define TIME_UP 500
#define FONT_SIZE 24

// extern const int8_t g_dirX[8] = { 0, 0, 1, -1, 1, -1, 1, -1};
// extern const int8_t g_dirY[8] = { 1, -1, 0, 0, 1, -1, -1, 1};

enum side {
  LEFT,
  RIGHT,
};

enum player {
  EMPTY,
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

typedef std::bitset<PARTTERN_SIZE> patternBitset;
typedef std::bitset<9> patternMerge;

typedef struct s_pattern {
  const patternMerge player;
  const patternMerge opponent;
  const int length;
  const int value;
} t_pattern;

const std::array<const t_pattern, 2> patternsArray{{
    {patternMerge("000001111"), patternMerge("000000000"), 4, 1000},
    {patternMerge("000001101"), patternMerge("000000010"), 4, -1111},
}};

bool handleMouse(int mouseX, int mouseY);
int modeSelection(Game& game, Render& render, Button& player, Button& IA);
void start_menu(Render& render, Button& player, Button& IA);
int gameChecker(Game&, int, int, int, Render& render);
void place_stone(Game& board, Render& render, int x, int y, int& player);
bool isCapture(Game& game, int checkY, int checkX, int dirY, int dirX,
               int player);
bool posValid(Game& game, int x, int y, int player);

#endif