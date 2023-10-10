#include "../inc/MinMax.hpp"

MinMax::MinMax(int depth, SDL_Renderer *renderer): 
    _depth(depth),
    _renderer(renderer) {}

MinMax::~MinMax() {}

cost MinMax::minMaxRecursive(const vector2d &board, int player, int depth, const int yGame, const int xGame, int alpha, int beta) {
    if (depth == 0 || checkWin(board, yGame, xGame, player) == true) {
        Heuristic computeH(player, board);
        return cost{ heuristic(board, player), xGame, yGame};
        // return cost{ computeH.heuristic(), xGame, yGame};
    }

    int value = (player == _initPlayer) ? INT_MIN : INT_MAX;
    std::vector<cost> result;
    bool cutoff = false;
    for (int y = 0; y < BOARD_SIZE && !cutoff; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (board[y][x] == 0 && emptyNeighbour(board, x, y) == false) {
                vector2d copy = board;
                copy[y][x] = player;
                if (checkWin(copy, y, x, player) && depth == _depth)
                    return cost{INT_MAX, x, y};
                int next_player = (player == BLACK) ? WHITE : BLACK;
                cost recursiveResult = minMaxRecursive(copy, next_player, depth - 1, y, x, alpha, beta);
                result.push_back(cost{recursiveResult.heuristic, x, y});

                if (player == _initPlayer){
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

    if (_initPlayer == player) {
        cost finalValue = finCorrectValue(result, MAX);
        return finalValue;
    }

    cost finalValue = finCorrectValue(result, MIN);
    return finalValue;
}

void MinMax::minMaxAlgorithm(vector2d &board, int player, int captureCounter[2])
{
    _initPlayer = player;
    _captureCounter[0] = captureCounter[0];
    _captureCounter[1] = captureCounter[1];
    cost result = minMaxRecursive(board, _initPlayer, _depth, 0, 0, INT_MIN, INT_MAX);
    std::cout << "heuristic:" << result.heuristic << " X: " << result.x << " Y: " << result.y <<"\n";
    place_stone(board, _initPlayer, _renderer, result.y, result.x, _captureCounter);
}

int MinMax::checkWin(const vector2d& board, const int y, const int x, const int player){
    const int   dirX[] = { 0, 0, 1, -1, 1, -1, 1, -1};
    const int   dirY[] = { 1, -1, 0, 0, 1, -1, -1, 1};
    int         checkX = 0, checkY = 0;
    int         count[2] = {1, 1};

    for (int i = 0; i < 8; i++){
        for (int j = 1; j < 5; j++){
            checkX = x + (dirX[i] * j);
            checkY = y + (dirY[i] * j);
            if (checkX < 0 || checkY < 0 || checkX > BOARD_SIZE || checkY > BOARD_SIZE)
                break ;

            
            if (board[checkY][checkX] != player)
                break ;
            else
                (count[i % 2])++;
        }
        if (i % 2 == 1){
            if (count[(i - 1) / 2 % 2] >= 5)
                return (true);
            count[(i - 1) / 2 % 2] = 1;
        }
    }
    return (false);
}

cost MinMax::finCorrectValue(const std::vector<cost>& recursiveResult, int minOrMax){
    int cmp = 0;
    
    if (minOrMax == MAX)
        cmp = INT_MIN;
    else
        cmp = INT_MAX;
    
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

bool MinMax::emptyNeighbour(const vector2d &game, const int x, const int y){
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
