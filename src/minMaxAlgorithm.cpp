#include "../inc/minMaxAlgorithm.hpp"
#include <random>

void print_game(const vector2d& game) {
    const int game_size = game.size();
    for (int i = 0; i < game_size; i++) {
        for (int j = 0; j < game_size; j++)
            std::cout << game[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

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