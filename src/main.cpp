#include "../inc/gomoku.hpp"

void render_board(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 205, 127, 50, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Draw grid of 19 * 19
    for (int x = MARGIN; x < SCREEN_WIDTH - MARGIN; x += GRID_SIZE) {
        SDL_RenderDrawLine(renderer, x, MARGIN, x, SCREEN_HEIGHT - MARGIN * 2);
        SDL_RenderDrawLine(renderer, MARGIN, x, SCREEN_WIDTH - MARGIN * 2, x);
    }
    SDL_RenderPresent(renderer);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Failed to init SDL: %s", SDL_GetError());
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("Gomoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); 
    if (!window) {
        SDL_Log("Failed to create SDL window: %s", SDL_GetError());
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Failed to create SDL renderer: %s", SDL_GetError());
        return 1;
    }
    
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        // Handle q and echap for quit the programm
        // If SDL receive an event SDL_PollEvent return 1
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX;
                int mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                std::cout << "X: " << mouseX << "\n";
                std::cout << "Y: " << mouseY << "\n";

            }
            if (e.type == SDL_QUIT)
                quit = true;
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q)
                    quit = true;
            }
        }
        render_board(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}