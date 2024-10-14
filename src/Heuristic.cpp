#include "../inc/Heuristic.hpp"

Heuristic::~Heuristic(){
}

Heuristic::Heuristic(const Board& game, int x, int y) :
    _game(game),
    _heuristic(0),
    _xPos(x),
    _yPos(y)
{
    this->globalHeuristic();
}

Heuristic::Heuristic(const Heuristic &cpy):
    _game(cpy._game),
    _heuristic(cpy._heuristic),
    _xPos(cpy._xPos),
    _yPos(cpy._yPos)
{
}


Heuristic &Heuristic::operator=(const Heuristic &rhs)
{
    if (this != &rhs)
    {
        this->_game = rhs._game;
        this->_heuristic = rhs._heuristic;
        this->_xPos = rhs._xPos;
        this->_yPos = rhs._yPos;
    }

    return (*this);
}

const Board& Heuristic::getGame() const { return (this->_game); }


// int Heuristic::counterAnalysis(int count, int opponent, bool capture, int empty, int inRow, int initPlayer) {
//     int result = 0;
//     std::cout << opponent << std::endl;
//     if (inRow >= 5)
//         result = INT32_MAX - 1;
//     else if ((inRow >= 4 || count >= 5) && empty > 0 )
//         result = 1000000;
//     else if (opponent >= 4)
//         result = 900000;
//     else if ((inRow == 3 || count >= 4) && empty > 1)
//         result = 500000;
//     else if (opponent == 3)
//         result = 400000;
//     else if ((inRow == 3 || count >= 4) && empty > 0)
//         result = 10000;
//     else if (capture)
//         result = 1000;
//     else if ((inRow == 2 || count >= 3) && empty > 1)
//         result = 100;
//     else if ((inRow == 2 || count >= 3) && empty > 0)
//         result = 50;
//     else
//         result = 5 * count + 5 * inRow + empty * 5;
    
//     if (this->getPlayer() != initPlayer)
//         result *= -1;
//     return (result);
// }

int Heuristic::counterAnalysis(int counter, int player, int color, bool openEnds) {
    int result = 0;

    if (counter == 5 && player == color)
        result = 10000;  // Higher value for a winning move
    else if (counter == 5 && player != color)
        result = 9000;   // High value for blocking an opponent's win
    else if (counter == 4 && player != color && openEnds)
        result = 800;    // Opponent open four
    else if (counter == 4 && player == color && openEnds)
        result = 700;    // Your open four
    else if (counter == 4 && player != color && !openEnds)
        result = 600;    // Opponent closed four (not as dangerous as open four)
    else if (counter == 4 && player == color && !openEnds)
        result = 500;    // Closed four
    else if (counter == 3 && player != color && openEnds)
        result = 300;    // Opponent open three
    else if (counter == 3 && player == color && openEnds)
        result = 250;    // Your open three
    else if (counter == 3 && player != color && !openEnds)
        result = 150;    // Opponent closed three
    else if (counter == 3 && player == color && !openEnds)
        result = 100;    // Closed three
    else
        result = counter * 50;  // Default weight for smaller patterns
    
    return result;
}

bool Heuristic::checkCapture(int checkY, int checkX, int dirY, int dirX, int player) {
    int enemy = (player == WHITE) ? BLACK : WHITE;

    if (checkX + dirX * 2 >= 0 && checkX + dirX * 2 < BOARD_SIZE
        && checkY + dirY * 2 >= 0 && checkY + dirY * 2 < BOARD_SIZE
        && this->_game.getPos(checkX + dirX, checkY + dirY) == enemy
        && this->_game.getPos(checkX + dirX * 2, checkY + dirY * 2) == player)
            return true;

    return false;
}

int Heuristic::localHeuristic(int x, int y) {
    int heuristic = 0;
    int player = this->_game.getPos(x, y);

    // Check all 4 directions (horizontal, vertical, and two diagonals)
    for (int i = 0; i < 4; i++) {
        int counter = 1;
        int color = 0;
        bool openEnds = false;

        // Forward check
        int checkX, checkY;
        for (int j = 1; j < 5; j++) {
            checkX = x + (dirX[i] * j);
            checkY = y + (dirY[i] * j);
            
            if (checkX < 0 || checkY < 0 || checkX >= BOARD_SIZE || checkY >= BOARD_SIZE) 
                break;
            if (this->_game.isPosEmpty(checkX, checkY)) {
                openEnds = true;  // There is space to extend the line
                break;
            }

            int posValue = this->_game.getPos(checkX, checkY);
            if (j == 1) color = posValue;

            if (posValue == color) 
                counter++;
            else
                break;
        }

        // Check the opposite direction to determine if it's an open-ended line
        for (int j = 1; j < 5; j++) {
            checkX = x - (dirX[i] * j);
            checkY = y - (dirY[i] * j);

            if (checkX < 0 || checkY < 0 || checkX >= BOARD_SIZE || checkY >= BOARD_SIZE)
                break;
            if (this->_game.isPosEmpty(checkX, checkY)) {
                openEnds = true;
                break;
            }

            int posValue = this->_game.getPos(checkX, checkY);
            if (posValue == color) 
                counter++;
            else
                break;
        }

        heuristic += counterAnalysis(counter, player, color, openEnds);
        
        // Add capture check heuristic
        if (this->checkCapture(y, x, dirY[i], dirX[i], player)) {
            heuristic -= 200;  // Penalize positions vulnerable to capture
        }
    }

    return heuristic;
}

// int Heuristic::localHeuristic(int x, int y){
//     int count[2] = {1, 1}, empty[2] = {0, 0}, opponent[2] = {0, 0}, inRow[2] = {1, 1};
//     bool capture[2] = {false, false}, rowChecker[2] = {true, true};
//     int localHeuristic = 0;
//     int index = 0;
//     int posToCheck;
//     int player = this->_game.getPos(x, y);
//     int checkX, checkY;

//     for (int i = 0; i < 8; i++) {
//         for (int j = 1; j < 5; j++) {
//             checkX = x + (dirX[i] * j);
//             checkY = y + (dirY[i] * j);
            
//             if (checkX < 0 || checkY < 0 || checkX >= BOARD_SIZE || checkY >= BOARD_SIZE)
//                 break;
            
//             posToCheck = this->_game.getPos(checkX, checkY);
            
//             if (posToCheck == player) {
//                 ++(count[i / 2]);
//                 if (rowChecker[i / 2]) {
//                     ++(inRow[i / 2]);
//                 }
//             } else if (posToCheck > 0 && posToCheck != player) {
//                 ++(opponent[i / 2]);
//                 if (checkCapture(checkY, checkX, dirY[i], dirX[i], player)) {
//                     capture[i / 2] = true;
//                 }
//                 break;
//             } else if (posToCheck == 0) {
//                 ++empty[i / 2];
//                 rowChecker[i / 2] = false;
//             } else {
//                 break;
//             }
//         }
        
//         if (i % 2 == 1) {
//             localHeuristic += counterAnalysis(count[index], opponent[index], capture[index], empty[index], inRow[index], player);
            
//             count[index] = 1;
//             inRow[index] = 1;
//             empty[index] = 0;
//             opponent[index] = 0;
//             capture[index] = false;
//             rowChecker[index] = true;
            
//             index = (index == 0) ? 1 : 0;
//         }
//     }

//     return (localHeuristic);
// }

int Heuristic::globalHeuristic(){
    this->_heuristic = 0;

    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
            if (this->_game.isPosEmpty(x, y) == true)
                continue ;
            this->_heuristic += this->localHeuristic(x, y);
        }
    }
    return (this->_heuristic);
}