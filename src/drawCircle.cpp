#include "../inc/gomoku.hpp"

void drawCircle(int centreX, int centreY, SDL_Renderer *renderer){
    // int x = RADIUS - 1;
    // int y = 0;
    // int distX = 1, distY =1;
    // int err = distX - (RADIUS * 2);

    // SDL_SetRenderDrawColor(renderer, 80, 0, 80, 255);
    // while (x >= y){
    //     // SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
    //     // SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
    //     // SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
    //     // SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
    //     // SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
    //     // SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
    //     // SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
    //     // SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

    //     SDL_RenderDrawLine(renderer, centreX + x, centreY + y, centreX - x, centreY + y);
    //     SDL_RenderDrawLine(renderer, centreX + x, centreY - y, centreX - x, centreY - y);

    //     SDL_RenderDrawLine(renderer, centreX + x, centreY + y, centreX + x, centreY - y);
    //     SDL_RenderDrawLine(renderer, centreX - x, centreY + y, centreX - x, centreY - y);
    //     if (err <= 0){
    //         y++;
    //         err += distY;
    //         distY += 2;
    //     }

    //     if (err > 0){
    //         x--;
    //         distX += 2;
    //         err += (distX - (RADIUS*2));
    //     }
    // }
    std::cout << "X:" << centreX << "\n";
    SDL_SetRenderDrawColor(renderer, 80, 0, 80, 255);
    for (int w = 0; w < RADIUS * 2; w++)
    {
        for (int h = 0; h < RADIUS * 2; h++)
        {
            int dx = RADIUS - w; // horizontal offset
            int dy = RADIUS - h; // vertical offset
            if ((dx*dx + dy*dy) <= (RADIUS * RADIUS))
            {
                SDL_RenderDrawPoint(renderer, centreX + dx, centreY + dy);
            }
        }
    }
    SDL_RenderPresent(renderer);
}