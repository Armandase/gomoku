#include "../inc/gomoku.hpp"


int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;
    SDL_Window *window = SDL_CreateWindow("Gomoku", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); 
    if (!window)
        return 1;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        return 1;
    SDL_SetRenderDrawColor(renderer, 205, 127, 50, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect;
    for (int y = 1; y <= BOARD_HEIGHT; y++) {
        for (int x = 1; x <= BOARD_WIDTH; x++) {
            rect = {SCREEN_HEIGHT / 20 * x, SCREEN_WIDTH / 20 * y, 10, 10};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(5000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}