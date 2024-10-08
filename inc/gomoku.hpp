#ifndef __GOMOKU_HPP__
#define __GOMOKU_HPP__

# include <SDL.h>
# include <exception>
# include <iostream>
# include <vector>
# include <SDL_ttf.h>
# include <SDL_image.h>
# include <climits>
# include <set>
# include <bitset>
// # include "Board.hpp"
# include "Button.hpp"

# define GRID_SIZE 50
# define MARGIN 20
# define OFFSET 50
# define BOARD_SIZE 18
# define SCREEN_HEIGHT ((GRID_SIZE * BOARD_SIZE) + (2 * (MARGIN)))
# define SCREEN_WIDTH ((GRID_SIZE * BOARD_SIZE) + (2 * (MARGIN + OFFSET)))
# define RADIUS (GRID_SIZE / 3)
# define DIAMETER (RADIUS * 2)
# define DEPTH 4
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

typedef std::bitset<PARTTERN_SIZE> patternBitset;
typedef std::vector<patternBitset> patternsVector;

void    drawCircle(int, int, SDL_Renderer *);
int     handleMouse(Board& board, int& player, SDL_Renderer* renderer);
int     handleStart(SDL_Renderer *, Button &player, Button &IA);
void    start_menu(SDL_Renderer *, Button &player, Button &IA);
void    render_board(SDL_Renderer *);
int     gameChecker(Board&, const int&, const int&, const int&, SDL_Renderer*);
int     place_stone(Board& board, int& player, SDL_Renderer *renderer, const int& y, const int& x);
bool    checkCapture(const Board& game, int checkY, int checkX, int dirY, int dirX, int player);

#endif