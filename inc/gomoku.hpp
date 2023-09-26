#ifndef GOMOKU_HPP
# define GOMOKU_HPP

# include <SDL.h>
# include <exception>
# include <iostream>
# include <vector>
# include <SDL_ttf.h>
# include <SDL_image.h>
# include <climits>

# define GRID_SIZE 50
# define MARGIN 20
# define BOARD_SIZE 18
# define SCREEN_HEIGHT ((GRID_SIZE * BOARD_SIZE) + (2 * MARGIN))
# define SCREEN_WIDTH ((GRID_SIZE * BOARD_SIZE) + (2 * MARGIN))
# define RADIUS (GRID_SIZE / 3)
# define DIAMETER (RADIUS * 2)

class Button;

enum player {
    WHITE = 1,
    BLACK,
};

enum mode {
    PLAYER_MODE = 1,
    IA_MODE,
};

typedef std::vector<std::vector<int> > vector2d;

void    drawCircle(int, int, SDL_Renderer *);
int     handleMouse(vector2d& game, int& player, SDL_Renderer* renderer);
int     handleStart(SDL_Renderer *, Button &player, Button &IA);
void    start_menu(SDL_Renderer *, Button &player, Button &IA);
void    render_board(SDL_Renderer *);
int     gameChecker(vector2d&, const int&, const int&, const int&, SDL_Renderer*);
int     place_stone(vector2d& game, int& player, SDL_Renderer *renderer, const int& y, const int& x);



#endif