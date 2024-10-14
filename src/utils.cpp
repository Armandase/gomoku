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