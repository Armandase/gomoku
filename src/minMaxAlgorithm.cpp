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

cost finCorrectValue(const std::vector<cost>& recursiveResult, int minOrMax){
    int cmp = 0;
    
    if (minOrMax == MAX)
        cmp = -2147483648;
    else
        cmp = 2147483647;
    
    int size = recursiveResult.size();
    if (!size)
        std::cout << "Empty vector of recursive\n";
    int pos = -1;
    for (int i = 0; i < size; i++){
        if (minOrMax == MAX && recursiveResult[i].heuristic > cmp){
            cmp = recursiveResult[i].heuristic;
            pos = i;
        } else if (minOrMax == MIN && recursiveResult[i].heuristic < cmp){
            cmp = recursiveResult[i].heuristic;
            pos = i;
        }
    }
    if (pos == -1){
        std::cout << "Min value not found\n";
        return cost{0,0,0};
    }
    return recursiveResult[pos];
}

int checkWin(const vector2d& game, const int& y, const int& x, const int& player){
    const int   dirX[] = { 0, 1, 0, -1, 1, -1, 1, -1};
    const int   dirY[] = { 1, 0, -1, 0, 1, -1, -1, 1};
    int         checkX = 0, checkY = 0;

    int         result = 0;

    for (int i = 0; i < 8; i++){
        for (int j = 1; j < 5; j++){
            checkX = x + (dirX[i] * j);
            checkY = y + (dirY[i] * j);
            if (checkX < 0 || checkY < 0 || checkX > 18 || checkY > 18)
                break ;

            
            if (game[checkY][checkX] != player)
                break ;
            else if (j == 4)
                return (true);
        }
    }
    return (false);
}

cost minMaxRecursive(const vector2d &game, int init_player, int player, int depth, const int yGame, const int xGame) {
    if (depth == 0 || checkWin(game, yGame, xGame, player) == true) {
        return cost{heuristic(game, player, yGame, xGame), xGame, yGame};
    }

    std::vector<cost> result;
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (game[y][x] == 0 && emptyNeighbour(game, x, y) == false) {
                vector2d copy = game;
                copy[y][x] = player;
                if (checkWin(copy, y, x, player) && depth == 2)
                    return cost{INT_MAX, x, y};
                int next_player = (player == BLACK) ? WHITE : BLACK;
                cost recursiveResult = minMaxRecursive(copy, init_player, next_player, depth - 1, y, x);
                result.push_back(cost{recursiveResult.heuristic, x, y});
            }
        }
    }

    if (init_player == player) {
        cost finalValue = finCorrectValue(result, MAX);
        return finalValue;
    }

    cost finalValue = finCorrectValue(result, MIN);
    return finalValue;
}

void minMaxAlgorithm(vector2d &game, int &player, SDL_Renderer *renderer)
{
    cost result =  minMaxRecursive(game, player, player, 2, 0, 0);
    std::cout << "heuristic:" << result.heuristic << " X: " << result.x << " Y: " << result.y <<"\n";
    place_stone(game, player, renderer, result.y, result.x);
}