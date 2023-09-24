#include "../inc/gomoku.hpp"
#include "../inc/Button.hpp"

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
    SDL_RenderPresent(renderer);
}
