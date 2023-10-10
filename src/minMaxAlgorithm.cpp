#include "../inc/minMaxAlgorithm.hpp"
#include "../inc/utils.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>

bool emptyNeighbour(const vector2d &game, const int x, const int y){
    const int   dirX[] = { 0, 0, 1, -1, 1, -1, 1, -1};
    const int   dirY[] = { 1, -1, 0, 0, 1, -1, -1, 1};
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
        std::cout << "Value not found\n";
        return cost{0,0,0};
    }
    return recursiveResult[pos];
}

bool checkWin(const vector2d& game, const int& y, const int& x, const int& player){
    const int   dirX[] = { 0, 0, 1, -1, 1, -1, 1, -1};
    const int   dirY[] = { 1, -1, 0, 0, 1, -1, -1, 1};
    int         checkX = 0, checkY = 0;
    int         count[2] = {1, 1};

    int current = 0;
    for (int i = 0; i < 8; i++){
        for (int j = 1; j < 5; j++){
            checkX = x + (dirX[i] * j);
            checkY = y + (dirY[i] * j);
            if (checkX < 0 || checkY < 0 || checkX > BOARD_SIZE || checkY > BOARD_SIZE)
                break ;

            
            if (game[checkY][checkX] != player)
                break ;
            else if (game[checkY][checkX] == player)
                ++(count[i / 2 % 2]);
        }
        if (i % 2 == 1){
            if (count[current] >= 5)
                return (true);
            count[current] = 1;
            (current == 0) ? current = 1 : current = 0;
        }
    }
    return (false);
}

void    removeCapture(vector2d& copy, int y, int x, int player){
    const int   dirX[] = { 0, 0, 1, -1, 1, -1, 1, -1};
    const int   dirY[] = { 1, -1, 0, 0, 1, -1, -1, 1};

    for (int i = 0; i < 8; i++){
        if (checkCapture(copy, y, x, dirY[i], dirX[i], player) == true){
            copy[y + dirY[i]][x + dirX[i]] = 0;
            copy[y + (dirY[i] * 2)][x + (dirX[i] * 2)] = 0;
        }
    }
}

cost minMaxRecursive(const vector2d &game, int init_player, int player, int depth, const int yGame, const int xGame, int alpha, int beta) {
    if (depth == 0 || checkWin(game, yGame, xGame, player) == true) {
        Heuristic computeH(player, game);
        return cost{ computeH.heuristic(), xGame, yGame};
    }

    int value = (player == init_player) ? -2147483648 : 2147483647;
    std::vector<cost> result;
    bool cutoff = false;
    for (int y = 0; y < BOARD_SIZE && !cutoff; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (game[y][x] == 0 && emptyNeighbour(game, x, y) == false) {
                vector2d copy = game;
                copy[y][x] = player;
                if (checkWin(copy, y, x, player) && depth == DEPTH)
                    return cost{INT_MAX, x, y};

                removeCapture(copy, y, x, player);
                int next_player = (player == BLACK) ? WHITE : BLACK;
                cost recursiveResult = minMaxRecursive(copy, init_player, next_player, depth - 1, y, x, alpha, beta);
                result.push_back(cost{recursiveResult.heuristic, x, y});

                if (player == init_player){
                    if (recursiveResult.heuristic > value)
                        value = recursiveResult.heuristic;
                    if (value >= beta){
                        cutoff = true;
                        break ;
                    }
                    if (value > alpha)
                        alpha = value;
                }
                else {
                    if (recursiveResult.heuristic < value)
                        value = recursiveResult.heuristic;
                    if (value <= alpha){
                        cutoff = true;
                        break ;
                    }
                    if (value < beta)
                        beta = value;
                }
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
    int alpha = -2147483648, beta = 2147483647;

    clock_t begin = clock();
    cost result =  minMaxRecursive(game, player, player, DEPTH, 0, 0, alpha, beta);
	clock_t end = clock();
	double timer = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    std::cout << "heuristic:" << result.heuristic << " X: " << result.x << " Y: " << result.y <<"\n";
    {
        std::ostringstream message;
        message << std::fixed << std::setprecision(3) << timer;
        SDL_SetRenderDrawColor(renderer, 205, 127, 50, 255);

        SDL_Color textColor = {80, 0, 80, 255};
        SDL_Rect msg_rect = {SCREEN_WIDTH - MARGIN - OFFSET, SCREEN_HEIGHT - SCREEN_HEIGHT / 15, MARGIN + OFFSET, OFFSET};
        SDL_SetRenderDrawColor(renderer, 205, 127, 50, 255);
        SDL_RenderFillRect(renderer, &msg_rect);
        writeText(message.str(), "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", msg_rect, textColor, 24,renderer);
    }
    place_stone(game, player, renderer, result.y, result.x);

}