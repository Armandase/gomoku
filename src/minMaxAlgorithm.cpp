#include "../inc/minMaxAlgorithm.hpp"

int minMaxRecursive(const vector2d &game, const int& init_player, int player, int depth){
    if (depth == 0)
        return 1;
    std::vector<int> result;
    const int board_size = game.size();
    for (int x = 0; x < board_size;  x++) {
        for (int y = 0; y < board_size;  y++) {
            if (game[x][y] == 0) {
                vector2d copy = game;
                copy[x][y] = player;
                player == BLACK ? player = WHITE : player = BLACK;
                result.push_back(minMaxRecursive(copy, init_player, player, --depth));
            }
        }
    }
    if (init_player == player)
        // return *max(result.begin(), result.end());
        return 1;
    else
        return 0;
        // return *min(result.begin(), result.end());
}

void    minMaxAlgorithm(vector2d& game, int& player, SDL_Renderer *renderer){
    std::cout << minMaxRecursive(game, player, player, 2) << "\n";

}