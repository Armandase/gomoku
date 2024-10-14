#include "../inc/minMaxAlgorithm.hpp"


int indexOfMaxValue(const std::vector<Heuristic>& vec){
    int max = INT32_MIN;
    int idx = -1;
    int size = vec.size();

    for (int i = 0; i < size; i++){
        if (vec[i].getHeuristic() > max)
        {
            max = vec[i].getHeuristic();
            idx = i;
        }
    }
    if (idx == -1)
        throw std::runtime_error((std::string(__FUNCTION__ ) + std::string(": not found")));

    return idx;
}

int getCurrentPlayer(int depth, int initPlayer){
    if ((depth + 2) % 2 == DEPTH % 2)
        return initPlayer;
    return initPlayer == BLACK ? WHITE : BLACK;
}

heuristicSet generatePossibleMoves(Board& game, int player){
    heuristicSet possibleMoves;
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (game.isPosEmpty(x, y) == true && emptyNeighbour(game, x, y) == false) {
            // if (game.isPosEmpty(x, y) == true) {
                Board copy = game;
                copy.setPos(x, y, getCurrentPlayer(DEPTH, player));
                if (validGame(copy, y, x, player) == false)
                    continue;

                Heuristic h = Heuristic(copy, x, y);
                if (checkWin(h) == true){
                    h.setHeuristic(INT_MAX);
                    possibleMoves.insert(h);
                    return possibleMoves;
                }
                h.setHeuristic(h.localHeuristic(x, y));
                possibleMoves.insert(h);
            }
        }
    }
    return possibleMoves;
}

bool emptyNeighbour(const Board &game, const int x, const int y){
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
        if (game.isPosEmpty(checkX, checkY) == true)
            counter++;        
    }
    if (counter == 8)
        return (true);
    return (false);
}

bool checkWin(const Heuristic& heuristic){
    const int   dirX[] = { 0, 0, 1, -1, 1, -1, 1, -1};
    const int   dirY[] = { 1, -1, 0, 0, 1, -1, -1, 1};
    int         checkX = 0, checkY = 0;
    int         count[2] = {1, 1};

    int current = 0;
    for (int i = 0; i < 8; i++){
        for (int j = 1; j < 5; j++){
            checkX = heuristic.getX() + (dirX[i] * j);
            checkY = heuristic.getY() + (dirY[i] * j);
            if (checkX < 0 || checkY < 0 || checkX > BOARD_SIZE || checkY > BOARD_SIZE)
                break ;

            
            if (heuristic.getGame().getPos(checkX, checkY) != heuristic.getPlayer())
                break ;
            else if (heuristic.getGame().getPos(checkX, checkY) == heuristic.getPlayer())
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

//return false when there are a double three
bool    validGame(Board& copy, int yPoint, int xPoint, int player){
    const int   dirX[] = { 0, 0, 1, -1, 1, -1, 1, -1};
    const int   dirY[] = { 1, -1, 0, 0, 1, -1, -1, 1};
    
    if (copy.checkDoubleThree(xPoint, yPoint, player))
        return true;
        
    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
            if (copy.isPosEmpty(x, y) == true)
                continue;

            for (int i = 0; i < 8; i++){

                if (y == yPoint && x == xPoint && checkCapture(copy, y, x, dirY[i], dirX[i], player) == true){
                    copy.removePos(x + dirX[i], y + dirY[i]);
                    copy.removePos(x + (dirX[i] * 2), y + (dirY[i] * 2));
                }
            }
        }
    }
    return true;
}
