#include "../inc/gomoku.hpp"

void drawCircle(int centreX, int centreY, SDL_Renderer *renderer){
    centreX = centreX * GRID_SIZE + MARGIN ;
    centreY = centreY * GRID_SIZE + MARGIN ;
    int x = RADIUS - 1;
    int y = 0;
    int dx = 1, dy = 1;
    int err = dx - (RADIUS * 2);

    while (x >= y){
        SDL_RenderDrawLine(renderer, centreX + x, centreY - y, centreX + x, centreY + y);
        SDL_RenderDrawLine(renderer, centreX - x, centreY - y, centreX - x, centreY + y);
        SDL_RenderDrawLine(renderer, centreX + y, centreY - x, centreX + y, centreY + x);
        SDL_RenderDrawLine(renderer, centreX - y, centreY - x, centreX - y, centreY + x);
        if (err <= 0){
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (RADIUS * 2);
        }
    }
    SDL_RenderPresent(renderer);
}