#include "../inc/minMaxAlgorithm.hpp"

void print_game(const vector2d& game) {
    const int game_size = game.size();
    for (int i = 0; i < game_size; i++) {
        for (int j = 0; j < game_size; j++)
            std::cout << game[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int isWin(const vector2d& game, int y, int x){
    const int dirX[] = { 0, 1, 0, -1, 1, -1, 1, -1};
    const int dirY[] = { 1, 0, -1, 0, 1, -1, -1, 1};
    const int player = game[y][x];
    int checkX = 0, checkY = 0;
    
    for (int i = 0; i < 8; i++){
        for (int j = 1; j < 5; j++){
            checkX = x + (dirX[i] * j);
            checkY = y + (dirY[i] * j);
            if (checkX < 0 || checkY < 0 || checkX > 18 || checkY > 18)
                return (0);
            if (game[checkY][checkX] != player)
                break ;
            else if (j == 4)
                return (player);
        }
    }
    return (0);
}

int checkVictory(const vector2d& game){
    int result = 0;

    for (int i = 0; i < 19; i++)
        for (int j = 0; j < 19; j++)
            if (game[i][j] > 0 && (result = isWin(game, i, j)) > 0)
                return (result);
    return (0);
}

void    minMaxAlgorithm(vector2d& game){
    int win = checkVictory(game);

    if (win == BLACK)
        std::cout << "black win" << std::endl;
    else if (win == WHITE)
        std::cout << "white win" << std::endl;
    // print_game(game);
};