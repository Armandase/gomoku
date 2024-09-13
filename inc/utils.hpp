#ifndef UTILS_HPP
# define UTILS_HPP
# include "gomoku.hpp"
# include "../inc/Board.hpp"
# include <unistd.h>

void    SDL_Error(const std::string &, SDL_Window *, SDL_Renderer *);
void    TTF_Error(const std::string &, SDL_Window *, SDL_Renderer *);
void    writeText(const std::string&, const std::string&, const SDL_Rect, const SDL_Color&, const int &, SDL_Renderer *);
void    print_game(const vector2d& game);


#endif