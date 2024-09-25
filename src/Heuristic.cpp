#include "../inc/Heuristic.hpp"

Heuristic::~Heuristic(){
}

Heuristic::Heuristic(int player, const Board& game, int x, int y) :
    _gamePtr(std::make_shared<Board>(game)),
    _initPlayer(player),
    _heuristic(0),
    _index(0),
    _xPos(x),
    _yPos(y)
{
    this->heuristic();
}

const Board& Heuristic::getGame() const { return (*(this->_gamePtr.get())); }


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
        // && this->_game[checkY + dirY][checkX + dirX] == ennemy
        && this->_gamePtr.get()->getPos(checkX + dirX, checkY + dirY) == ennemy
        && checkX + dirX * 2 >= 0 && checkX + dirX * 2 <= BOARD_SIZE
        && checkY + dirY * 2 >= 0 && checkY + dirY * 2 <= BOARD_SIZE
        // && this->_game[checkY + (dirY * 2)][checkX + (dirX * 2)] == player)
        && this->_gamePtr.get()->getPos(checkX + (dirX * 2), checkY + (dirY * 2)) == player)
            return true;
    return false;
}

int Heuristic::heuristic(){
    int checkX, checkY;
    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
            if (this->_gamePtr.get()->isPosEmpty(x, y) == true)
                continue ;
        
            int count[2] = {1, 1}, empty[2] = {0, 0}, inRow[2] = {1, 1};
            bool capture[2] = {false, false}, rowChecker[2] = {true, true};
            // int newPoint = this->_game[y][x];
            int newPoint = this->_gamePtr.get()->getPos(x, y);

            int playerPosition = 0;
            for (int i = 0; i < 8; i++) {
                for (int j = 1; j < 5; j++) {
                    checkX = x + (dirX[i] * j);
                    checkY = y + (dirY[i] * j);
                    if (checkX < 0 || checkY < 0 || checkX > BOARD_SIZE || checkY > BOARD_SIZE)
                        break ;
                    
                    playerPosition = this->_gamePtr.get()->getPos(checkX, checkY);
                    if (playerPosition == newPoint)
                        ++(count[i / 2 % 2]);
                    if (playerPosition == newPoint && rowChecker[i % 2])
                        ++(inRow[i / 2 % 2]);
                    if (playerPosition > 0 && playerPosition != newPoint
                        && checkCapture(checkY, checkX, dirY[i], dirX[i], newPoint)) {
                        capture[i / 2 % 2] = true;
                        break;
                    }
                    else if (playerPosition == 0){
                        ++empty[i / 2 % 2];
                        rowChecker[i / 2 % 2] = false;
                    }
                    else if (playerPosition != newPoint && playerPosition > 0 ){
                        break;
                    }
                    
                }
                if (i % 2 == 1){
                    this->_heuristic += counterAnalysis(count[_index], capture[_index], empty[_index], inRow[_index], newPoint);
                    count[_index] = 1;
                    inRow[_index] = 1;
                    empty[_index] = 0;
                    capture[_index] = false;
                    rowChecker[_index] = true;
                    this->_index = (this->_index == 0)? 1 : 0;
                }
            }
        }
    }
    return (this->_heuristic);
}