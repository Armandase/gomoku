#ifndef GOMOKU_HPP
# define GOMOKU_HPP

# include <SDL2/SDL.h>
# include <exception>
# include <iostream>
# include <vector>

# define GRID_SIZE 50
# define MARGIN 20
# define BOARD_WIDTH 19
# define BOARD_HEIGHT 19
# define SCREEN_HEIGHT (GRID_SIZE * 19) + (2 * MARGIN)
# define SCREEN_WIDTH (GRID_SIZE * 19) + (2 * MARGIN)
# define RADIUS (GRID_SIZE / 3)

enum player
{
    WHITE = 1,
    BLACK,
};

typedef std::vector<std::vector<int> > vector2d;

void drawCircle(int, int, SDL_Renderer *);

#endif