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
# define MARGIN 20
# define OFFSET 50
# define BOARD_SIZE 18
# define SCREEN_HEIGHT ((GRID_SIZE * BOARD_SIZE) + (2 * (MARGIN)))
# define SCREEN_WIDTH ((GRID_SIZE * BOARD_SIZE) + (2 * (MARGIN + OFFSET)))
# define RADIUS (GRID_SIZE / 3)
# define DIAMETER (RADIUS * 2)
# define DEPTH 3
# define PRUNING 10
# define PARTTERN_SIZE 4

enum player {
    WHITE = 1,
    BLACK,
};

enum mode {
    PLAYER_MODE = 1,
    IA_MODE,
};

class Board;
class Button;
class Render;

typedef std::bitset<PARTTERN_SIZE> patternBitset;
typedef std::vector<patternBitset> patternsVector;

int     handleMouse(Board& board, int& player, Render& render);
int     handleStart(Render& render, Button &player, Button &IA);
void    start_menu(Render& render, Button &player, Button &IA);
int     gameChecker(Board&, int, int, int, Render& render);
int     place_stone(Board& board, int& player, Render& render, const int& y, const int& x);
bool    checkCapture(const Board& game, int checkY, int checkX, int dirY, int dirX, int player);
bool    checkDoubleThree(Board& game, int col, int row);

#endif