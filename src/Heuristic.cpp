#include "../inc/Heuristic.hpp"

Heuristic::~Heuristic(){
}

Heuristic::Heuristic(int player, const vector2d& game) : _game(game), _initPlayer(player) {
    _heuristic = 0;
}

const vector2d Heuristic::getGame() const { return (this->_game); }


int Heuristic::counterAnalysis(int count, bool capture, int empty, int inRow, int player) {
    int result = 0;

    if (inRow >= 5)
        result = 1000000;
    else if ((inRow >= 4 || count >= 5) && empty > 0 )
        result = 500000;
    else if ((inRow == 3 || count >= 4) && empty > 1)
        result = 500000;
    else if ((inRow == 3 || count >= 4) && empty > 0)
        result = 100000;
    else if (capture)
        result = 10000;
    else if ((inRow == 2 || count >= 3) && empty > 1)
        result = 100;
    else if ((inRow == 2 || count >= 3) && empty > 0)
        result = 50;
    else
        result = 5 * count + 5 * inRow + empty * 5;
    
    if (player != this->_initPlayer)
        result *= -1;
    return (result);
}

bool Heuristic::checkCapture(int checkY, int checkX, int dirY, int dirX, int player) {
    int ennemy = (player == WHITE) ? BLACK : WHITE;

    if (checkY + dirY >= 0 && checkY + dirY <= BOARD_SIZE 
        && checkX + dirX >= 0 && checkX + dirX <= BOARD_SIZE
        && this->_game[checkY + dirY][checkX + dirX] == ennemy
        && checkX + dirX * 2 >= 0 && checkX + dirX * 2 <= BOARD_SIZE
        && checkY + dirY * 2 >= 0 && checkY + dirY * 2 <= BOARD_SIZE
        && this->_game[checkY + (dirY * 2)][checkX + (dirX * 2)] == player)
            return true;
    return false;
}

int Heuristic::heuristic(){
    int checkX, checkY;
    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
            if (this->_game[y][x] == 0)
                continue ;

            int count[2] = {1, 1}, empty[2] = {0, 0}, inRow[2] = {1, 1};
            bool capture[2] = {false, false}, rowChecker[2] = {true, true};
            int newPoint = this->_game[y][x];

            for (int i = 0; i < 8; i++) {
                for (int j = 1; j < 5; j++) {
                    checkX = x + (dirX[i] * j);
                    checkY = y + (dirY[i] * j);
                    if (checkX < 0 || checkY < 0 || checkX > BOARD_SIZE || checkY > BOARD_SIZE)
                        break ;
                    
                    if (this->_game[checkY][checkX] == newPoint)
                        (count[i % 2])++;
                    if (this->_game[checkY][checkX] == newPoint && rowChecker[i % 2])
                        (inRow[i % 2])++;
                    if (this->_game[checkY][checkX] > 0 && this->_game[checkY][checkX] != newPoint
                        && checkCapture(checkY, checkX, dirY[i], dirX[i], newPoint)) {
                        capture[i % 2] = true;
                        break;
                    }
                    else if (this->_game[checkY][checkX] == 0){
                        empty[i % 2]++;
                        rowChecker[i % 2] = false;
                    }
                    else if (this->_game[checkY][checkX] != newPoint && this->_game[checkY][checkX] > 0 ){
                        break;
                    }
                    
                }
                if (i % 2 == 1){
                    int index = (i - 1) / 2 % 2;
                    this->_heuristic += counterAnalysis(count[index], capture[index], empty[index], inRow[index], newPoint);
                    count[index] = 1;
                    inRow[index] = 1;
                    empty[index] = 0;
                    capture[index] = false;
                    rowChecker[index] = true;
                }
            }
        }
    }
    return (this->_heuristic);
}