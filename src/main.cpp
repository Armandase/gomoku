#include "../inc/gomoku.hpp"
#include "../inc/utils.hpp"
#include "../inc/minMaxAlgorithm.hpp"
#include "../inc/Button.hpp"

void render_board(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 205, 127, 50, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Draw grid of 19 * 19
    for (int x = MARGIN; x < SCREEN_WIDTH; x += GRID_SIZE) {
        SDL_RenderDrawLine(renderer, x, MARGIN, x, SCREEN_HEIGHT - MARGIN);
        SDL_RenderDrawLine(renderer, MARGIN, x, SCREEN_WIDTH - MARGIN, x);
    }
    SDL_RenderPresent(renderer);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        SDL_Error("Failed to init SDL:", NULL, NULL);
    SDL_Window *window = SDL_CreateWindow("Gomoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); 
    if (!window)
        SDL_Error("Failed to create SDL window:", window, NULL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        SDL_Error("Failed to create SDL renderer:", window, renderer);
    bool quit = false;
    SDL_Event e;
    // render_board(renderer);

    int player = WHITE;
    bool start = false;
    // create 2 button 
    Button playerButton(SCREEN_WIDTH / 3 - 100, SCREEN_HEIGHT / 2 - 50, 200, 100);
    Button IAButton(SCREEN_WIDTH / 3 * 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 100);
    start_menu(renderer, playerButton, IAButton);

    vector2d game(BOARD_HEIGHT + 1, std::vector<int>(BOARD_WIDTH + 1, 0));
    while (!quit) {
        // Handle q and echap for quit the programm
        // If SDL receive an event SDL_PollEvent return 1
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                quit = true;
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q)
                    quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (!start)
                    start = handleStart(renderer, playerButton, IAButton);
                else if (start && handleMouse(game, player, renderer))
                    continue ;
                SDL_RenderPresent(renderer);
                // minMaxAlgorithm(game);
            }
        }
    
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}