#include "../inc/gomoku.hpp"

void drawCircle(int centreX, int centreY, SDL_Renderer *renderer){
    int x = RADIUS - 1;
    int y = 0;
    int distX = 1, distY =1;
    int err = distX - (RADIUS * 2);

    SDL_SetRenderDrawColor(renderer, 80, 0, 80, 255);
    while (x >= y){
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);
        if (err <= 0){
            y++;
            err += distY;
            distY += 2;
        }

        if (err > 0){
            x--;
            distX += 2;
            err += (distX - (RADIUS*2));
        }
    }
    SDL_RenderPresent(renderer);
}