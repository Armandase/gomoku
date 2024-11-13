#include "../inc/gomoku.hpp"

void    writeText(const std::string& msg, const std::string& font, const SDL_Rect rect, const SDL_Color& color, const int &size, SDL_Renderer *renderer){
    TTF_Font* Font = TTF_OpenFont(font.c_str(), size);
    SDL_Surface* surfaceMsg = TTF_RenderText_Solid(Font, msg.c_str(), color);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMsg);
    SDL_RenderCopy(renderer, Message, NULL, &rect);
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(surfaceMsg);
    SDL_DestroyTexture(Message);
    TTF_CloseFont(Font);
}

int modeSelection(Game& game, Render& render, Button &player, Button &IA) {
    int mouseX, mouseY;

    // get the coordinate of the click to know which button has been hit
    SDL_GetMouseState(&mouseX, &mouseY);
    if (player.inButton(mouseX, mouseY)) {
        render.renderBoard(game);
        return PLAYER_MODE;
    }
    if (IA.inButton(mouseX, mouseY)) {
        render.renderBoard(game);
        return IA_MODE;
    }
    return 0;
}

int intlen(int number) {
    if (number == 0)
        return 1;
    int length = 0;
    while (number != 0) {
        number /= 10;
        length++;
    }
    return length;
}

int coordToBoard(int coor)
{
    return ((coor - MARGIN) + GRID_SIZE / 2) / GRID_SIZE;
}

int boardToRender(int value)
{
    return (value * GRID_SIZE + MARGIN);
}