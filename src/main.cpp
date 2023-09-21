#include "../inc/gomoku.hpp"


int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;
    SDL_Window *window = SDL_CreateWindow("Gomoku", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGTH, SDL_WINDOW_SHOWN); 
    if (!window)
        return 1;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}