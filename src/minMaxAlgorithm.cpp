#include "../inc/minMaxAlgorithm.hpp"
#include "../inc/utils.hpp"

bool emptyNeighbour(const vector2d &game, const int x, const int y){
    const int   dirX[] = { 0, 1, 0, -1, 1, -1, 1, -1};
    const int   dirY[] = { 1, 0, -1, 0, 1, -1, -1, 1};
    int         checkX = 0, checkY = 0;
    int         counter = 0;

    for (int i = 0; i < 8; i++){
        checkX = x + dirX[i];
        checkY = y + dirY[i];
        if (checkX < 0 || checkY < 0 || checkX > BOARD_SIZE || checkY > BOARD_SIZE){
            counter++;
            continue;
        }
        if (game[checkY][checkX] == 0)
            counter++;        
    }
    if (counter == 8)
        return (true);
    return (false);
}

cost minMaxRecursive(const vector2d &game, int init_player, int player, int depth, const int yGame, const int xGame) {
    if (depth == 0)
        return cost{heuristic(game, player, yGame, xGame), xGame , yGame};

    std::vector<cost> result;
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (game[y][x] == 0 && emptyNeighbour(game, x, y) == false) {
                vector2d copy = game;
                copy[y][x] = player;
                int next_player = (player == BLACK) ? WHITE : BLACK;
                cost recursiveResult = minMaxRecursive(copy, init_player, next_player, depth - 1, y, x);
                cost tmp {recursiveResult.heuristic, x, y};
                result.push_back(tmp);
            }
        }
    }
    if (init_player != player) {
        int size = result.size();
        int max = 0;
        int pos = 0;
        for (int i = 0; i < size; i++){
            if (result[i].heuristic > max){
                max = result[i].heuristic;
                pos = i;
            }
        }
       if (max == 0)
            return cost{0,0,0};
        return result[pos];
    }
    else {
        int size = result.size();
        int min = 2147483647;
        int pos = 0;
        for (int i = 0; i < size; i++){
            if (result[i].heuristic < min){
                min = result[i].heuristic;
                pos = i;
            }
        }
        if (min == 2147483647)
            return cost{0,0,0};
        return result[pos];
    }
}

void minMaxAlgorithm(vector2d &game, int &player, SDL_Renderer *renderer)
{
    cost result =  minMaxRecursive(game, player, player, 2, 0, 0);
    std::cout << "heuristic:" << result.heuristic << " X: " << result.x << " Y: " << result.y <<"\n";
    place_stone(game, player, renderer, result.y, result.x);
}