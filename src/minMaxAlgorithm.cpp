#include "../inc/minMaxAlgorithm.hpp"
#include <random>


void    minMaxAlgorithm(vector2d& game, int& player, SDL_Renderer *renderer){
    // print_game(game);
    std::random_device rd;
    std::mt19937 gen(rd());
    int x, y;
    do {
        x = (gen() % 19);
        y = (gen() % 19);
    } while (game[y][x] > 0);
    place_stone(game, player, renderer, y, x);
};