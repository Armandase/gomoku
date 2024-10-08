#include "../inc/Heuristic.hpp"

Heuristic::~Heuristic(){
}

Heuristic::Heuristic(int player, const Board& game, int x, int y) :
    _gamePtr(std::make_shared<Board>(game)),
    _initPlayer(player),
    _heuristic(0),
    _xPos(x),
    _yPos(y)
{
    this->globalHeuristic();
}

Heuristic::Heuristic(const Heuristic &cpy):
    _gamePtr(cpy._gamePtr),
    _initPlayer(cpy._initPlayer),
    _heuristic(cpy._heuristic),
    _xPos(cpy._xPos),
    _yPos(cpy._yPos)
{
}


Heuristic &Heuristic::operator=(const Heuristic &rhs)
{
    if (this != &rhs)
    {
        this->_gamePtr = rhs._gamePtr;
        this->_initPlayer = rhs._initPlayer;
        this->_heuristic = rhs._heuristic;
        this->_xPos = rhs._xPos;
        this->_yPos = rhs._yPos;
    }

    return (*this);
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

    if (checkX + dirX * 2 >= 0 && checkX + dirX * 2 <= BOARD_SIZE
        && checkY + dirY * 2 >= 0 && checkY + dirY * 2 <= BOARD_SIZE
        && this->_gamePtr.get()->getPos(checkX + dirX, checkY + dirY) == ennemy
        && this->_gamePtr.get()->getPos(checkX + (dirX * 2), checkY + (dirY * 2)) == player)
            return true;
    return false;
}

int Heuristic::localHeuristic(int x, int y){
    int count[2] = {1, 1}, empty[2] = {0, 0}, inRow[2] = {1, 1};
    bool capture[2] = {false, false}, rowChecker[2] = {true, true};
    int localHeuritic = 0;
    int index = 0;
    int posToCheck;
    int player = this->_gamePtr.get()->getPos(x, y);
    int checkX, checkY;


    for (int i = 0; i < 8; i++) {
        for (int j = 1; j < 5; j++) {
            checkX = x + (dirX[i] * j);
            checkY = y + (dirY[i] * j);
            if (checkX < 0 || checkY < 0 || checkX > BOARD_SIZE || checkY > BOARD_SIZE)
                break ;
            
            posToCheck = this->_gamePtr.get()->getPos(checkX, checkY);
            if (posToCheck == player)
                ++(count[i / 2 % 2]);
            if (posToCheck == player && rowChecker[i % 2])
                ++(inRow[i / 2 % 2]);
            if (posToCheck > 0 && posToCheck != player
                && checkCapture(checkY, checkX, dirY[i], dirX[i], player)) {
                capture[i / 2 % 2] = true;
                break;
            }
            else if (posToCheck == 0){
                ++empty[i / 2 % 2];
                rowChecker[i / 2 % 2] = false;
            }
            else if (posToCheck != player && posToCheck > 0 ){
                break;
            }
            
        }
        if (i % 2 == 1){
            localHeuritic += counterAnalysis(count[index], capture[index], empty[index], inRow[index], player);
            count[index] = 1;
            inRow[index] = 1;
            empty[index] = 0;
            capture[index] = false;
            rowChecker[index] = true;
            index = (index == 0)? 1 : 0;
        }
    }
    return (localHeuritic);
}

int Heuristic::globalHeuristic(){
    this->_heuristic = 0;

    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
            if (this->_gamePtr.get()->isPosEmpty(x, y) == true)
                continue ;
        
            this->_heuristic += this->localHeuristic(x, y);
        }
    }
    return (this->_heuristic);
}