#include "../inc/gomoku.hpp"
#include "../inc/utils.hpp"
#include "../inc/Button.hpp"
#include "../inc/Game.hpp"
#include "../inc/Render.hpp"

// Function to initialize the SDL window and run the game loop
int main(int argc, char const *argv[]) {
    Render render;
    render.init_sdl("Gomoku", SCREEN_WIDTH, SCREEN_HEIGHT);

    int start = 0;
    bool quit = false;
    SDL_Event e;
    int player = WHITE;
    int mouseX, mouseY;

    // Create buttons for choosing human vs AI or human vs human
    Button playerButton(SCREEN_WIDTH / 3 - 150, SCREEN_HEIGHT / 2 - 50, 300, 100);
    Button IAButton(SCREEN_WIDTH / 3 * 2 - 150, SCREEN_HEIGHT / 2 - 50, 300, 100);

    // Render Start Menu
    start_menu(render, playerButton, IAButton);   

    Game board;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true;
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q) quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (!start) {
                    start = handleStart(render, playerButton, IAButton);
                    continue;
                }
                SDL_GetMouseState(&mouseX, &mouseY);
                if ((player == WHITE || start == PLAYER_MODE) && handleMouse(mouseX, mouseY)) {
                    int x = coordToBoard(mouseX);
                    int y = coordToBoard(mouseY);
                    if (posValid(board, player, x, y)) {
                        place_stone(board, player, render, x, y);
                    }
                }
                SDL_RenderPresent(render.getRenderer());
            }
        }
    }
}
