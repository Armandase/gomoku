#include "../inc/gomoku.hpp"

void SDL_Error(const std::string &mess, SDL_Window *window, SDL_Renderer *renderer) {
    SDL_Log((mess + " %s").c_str(), SDL_GetError());
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window) {
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    exit(1);
}

void TTF_Error(const std::string &mess, SDL_Window *window, SDL_Renderer *renderer) {
    SDL_Log((mess + " %s").c_str(), TTF_GetError());
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window) {
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    exit(1);
}

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