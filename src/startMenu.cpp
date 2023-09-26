#include "../inc/gomoku.hpp"
#include "../inc/Button.hpp"
#include "../inc/utils.hpp"

int handleStart(SDL_Renderer *renderer, Button &player, Button &IA) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (player.inButton(mouseX, mouseY)) {
        render_board(renderer);
        return PLAYER_MODE;
    }
    if (IA.inButton(mouseX, mouseY)) {
        render_board(renderer);
        return IA_MODE;
    }
    return 0;
}

void start_menu(SDL_Renderer *renderer, Button &player, Button &IA) {
    SDL_SetRenderDrawColor(renderer, 205, 127, 50, 255);
    SDL_RenderClear(renderer);
    IA.renderButton(renderer, 205, 127, 50);
    player.renderButton(renderer,205, 127, 50);
    SDL_Rect playerText = {SCREEN_WIDTH / 3 - 140, SCREEN_HEIGHT / 2 - 50, 280, 100};
    writeText("Player VS Player", "fonts/OpenSans-Bold.ttf",
                playerText, {0, 0, 0, 255}, 50, renderer);
    SDL_Rect IAText = {SCREEN_WIDTH / 3 * 2 - 140, SCREEN_HEIGHT / 2 - 50, 280, 100};
    writeText("Player VS IA", "fonts/OpenSans-Bold.ttf",
                IAText, {0, 0, 0, 255}, 50, renderer);
    SDL_Rect titleText = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 4 - 50, 200, 100};
    writeText("GOMOKU", "fonts/OpenSans-Bold.ttf", 
                titleText, {0, 0, 0, 255}, 24, renderer);
    SDL_Rect creditText = {SCREEN_WIDTH - 310, SCREEN_HEIGHT - 110, 300, 100};
    writeText("made by adamiens & nlocusso", "fonts/OpenSans-Bold.ttf", 
                creditText, {0, 0, 0, 255}, 50, renderer);
    SDL_RenderPresent(renderer);
}
