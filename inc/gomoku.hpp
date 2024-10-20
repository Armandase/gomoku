#ifndef __GOMOKU_HPP__
#define __GOMOKU_HPP__

# include <exception>
# include <iostream>
# include <vector>
# include <climits>
# include <set>
# include <bitset>
# include "Button.hpp"
# include "Render.hpp" 

# define GRID_SIZE 50
# define MARGIN 40
# define OFFSET (MARGIN + 200)
# define BOARD_SIZE 18
# define BOARD_DIMENSIONS (GRID_SIZE * BOARD_SIZE)
# define SCREEN_HEIGHT (BOARD_DIMENSIONS + (2 * (MARGIN)))
# define SCREEN_WIDTH (BOARD_DIMENSIONS + MARGIN + OFFSET)
# define RADIUS (GRID_SIZE / 3)
# define DIAMETER (RADIUS * 2)
# define DEPTH 3
# define PRUNING 10
# define PARTTERN_SIZE 5
# define FONT_SIZE 24

// extern const int8_t g_dirX[8] = { 0, 0, 1, -1, 1, -1, 1, -1};
// extern const int8_t g_dirY[8] = { 1, -1, 0, 0, 1, -1, -1, 1};

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
typedef std::vector<patternBitset> patternsVector;

bool    handleMouse(int mouseX, int mouseY);
int     modeSelection(Game& game, Render& render, Button &player, Button &IA);
void    start_menu(Render& render, Button &player, Button &IA);
int     gameChecker(Game&, int, int, int, Render& render);
void    place_stone(Game& board, Render& render, int x, int y, int& player);
bool    isCapture(Game& game, int checkY, int checkX, int dirY, int dirX, int player);
bool    posValid(Game& game, int x, int y, int player);

#endif