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
    IA.renderButton(renderer, 255, 0, 0);
    player.renderButton(renderer, 255, 0, 0);
    SDL_Rect playerText = {SCREEN_WIDTH / 3 - 100, SCREEN_HEIGHT / 2 - 50, 200, 100};
    writeText("Player VS Player", "fonts/SEASRN.ttf", playerText, {255, 255, 255, 255}, renderer);
    SDL_Rect IAText = {SCREEN_WIDTH / 3 * 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 100};
    writeText("Player VS IA", "fonts/SEASRN.ttf", IAText, {255, 255, 255, 255}, renderer);
    SDL_Rect titleText = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 4 - 50, 200, 100};
    writeText("GOMOKU", "fonts/SEASRN.ttf", titleText, {255, 255, 255, 255}, renderer);
    SDL_RenderPresent(renderer);
}
