#ifndef GOMOKU_HPP
# define GOMOKU_HPP

# include <SDL2/SDL.h>
# include <exception>
# include <iostream>

#define GRID_SIZE 50
#define MARGIN 20
#define BOARD_WIDTH 19
#define BOARD_HEIGHT 19
#define SCREEN_HEIGHT (GRID_SIZE * 19) + (3 * MARGIN)
#define SCREEN_WIDTH (GRID_SIZE * 19) + (3 * MARGIN)
#define RADIUS GRID_SIZE / 3

void drawCircle(int centreX, int centreY, SDL_Renderer *renderer);

#endif