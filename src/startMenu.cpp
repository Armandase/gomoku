#include "../inc/gomoku.hpp"
#include "../inc/Button.hpp"
#include "../inc/utils.hpp"
#include "../inc/Render.hpp"

// called when a player click on one of the available buttons
// return the game mode or 0 if the click wasn't on a button
int handleStart(Render& render, Button &player, Button &IA) {
    int mouseX, mouseY;

    // get the coordinate of the click to know which button has been hit
    SDL_GetMouseState(&mouseX, &mouseY);
    if (player.inButton(mouseX, mouseY)) {
        render.renderBoard();
        return PLAYER_MODE;
    }
    if (IA.inButton(mouseX, mouseY)) {
        render.renderBoard();
        return IA_MODE;
    }
    return 0;
}

void start_menu(Render& render, Button &player, Button &IA) {
    SDL_SetRenderDrawColor(render.getRenderer(), 205, 127, 50, 255);
    SDL_RenderClear(render.getRenderer());
    IA.renderButton(render.getRenderer(), 205, 127, 50);
    player.renderButton(render.getRenderer(),205, 127, 50);
    SDL_Rect playerText = {SCREEN_WIDTH / 3 - 140, SCREEN_HEIGHT / 2 - 50, 280, 100};

    SDL_SetRenderDrawColor(render.getRenderer(), 0, 0, 0, 255);
    SDL_RenderDrawRect(render.getRenderer(), &playerText);
    
    render.writeText("Player VS Player", "fonts/OpenSans-Bold.ttf",
                playerText, {0, 0, 0, 255}, 50);

    SDL_Rect IAText = {SCREEN_WIDTH / 3 * 2 - 140, SCREEN_HEIGHT / 2 - 50, 280, 100};
    SDL_SetRenderDrawColor(render.getRenderer(), 0, 0, 0, 255);
    SDL_RenderDrawRect(render.getRenderer(), &IAText);
    render.writeText("Player VS IA", "fonts/OpenSans-Bold.ttf",
                IAText, {0, 0, 0, 255}, 50);
    
    SDL_Rect titleText = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 4 - 50, 200, 100};
    render.writeText("GOMOKU", "fonts/OpenSans-Bold.ttf", 
                titleText, {0, 0, 0, 255}, 24);
    
    SDL_Rect creditText = {SCREEN_WIDTH - 310, SCREEN_HEIGHT - 70, 300, 50};
    render.writeText("made by adamiens & nlocusso", "fonts/OpenSans-Bold.ttf", 
                creditText, {0, 0, 0, 255}, 50);

    SDL_RenderPresent(render.getRenderer());
    

}
