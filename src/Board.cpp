#include "../inc/Board.hpp"

Board::Board():
    _player1(),
    _player1Diag(),
    _player1AntiDiag(),
    _player2(),
    _player2Diag(),
    _player2AntiDiag(),
    _idPlayer1(WHITE),
    _idPlayer2(BLACK)
{
    resetBoard();
}

Board::~Board(){

};

Board::Board(const Board &cpy):
    _player1(cpy._player1),
    _player1Diag(cpy._player1Diag),
    _player1AntiDiag(cpy._player1AntiDiag),
    _player2(cpy._player2),
    _player2Diag(cpy._player2Diag),
    _player2AntiDiag(cpy._player2AntiDiag),
    _width(cpy._width),
    _idPlayer1(cpy._idPlayer1),
    _idPlayer2(cpy._idPlayer2)
{
    generateDiagBoard();
    generateAntiDiagBoard();
    std::cout << "ORIGINAL" << std::endl;
    printBoard();
    std::cout << "DIAG" << std::endl;
    printDiagBoard();
    std::cout << "ANTI DIAG" << std::endl;
    printAntiDiagBoard();
}

Board &Board::operator=(const Board &rhs)
{
    if (this != &rhs)
    {
        this->_player1 = rhs._player1;
        this->_player1Diag = rhs._player1Diag;
        this->_player1AntiDiag = rhs._player1AntiDiag;
        this->_player2 = rhs._player2;
        this->_player2Diag = rhs._player2Diag;
        this->_player2AntiDiag = rhs._player2AntiDiag;
        this->_width = rhs._width;
        this->_idPlayer1 = rhs._idPlayer1;
        this->_idPlayer2 = rhs._idPlayer2;
    }
    return (*this);
}

void Board::setPos(int x, int y, int player)
{

    if (player == this->_idPlayer1 && !this->_player2.test(x + y * this->_width))
        this->_player1.set(x + y * this->_width);
    else if (player == this->_idPlayer2 && !this->_player1.test(x + y * this->_width))
        this->_player2.set(x + y * this->_width);
    else
        std::cerr << "Error: Invalid player ID" << std::endl;
}

void Board::removePos(int x, int y){
    if (this->_player1.test(x + y * this->_width))
        this->_player1.reset(x + y * this->_width);
    else if (this->_player2.test(x + y * this->_width))
        this->_player2.reset(x + y * this->_width);
}

int Board::getPos(int x, int y) const
{
    if (this->_player1.test(x + y * this->_width))
        return (this->_idPlayer1);
    else if (this->_player2.test(x + y * this->_width))
        return (this->_idPlayer2);
    else
        return (0);
}

void Board::printBoard() const{
    for (int y = 0; y < this->_width; y++){
        for (int x = 0; x < this->_width; x++){
            if (this->_player1.test(x + y * this->_width))
                std::cout << "1 ";
            else if (this->_player2.test(x + y * this->_width))
                std::cout << "2 ";
            else
                std::cout << "0 ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void Board::printDiagBoard() const{
    for (int y = 0; y < this->_width; y++){
        for (int x = 0; x < this->_width; x++){
            if (this->_player1Diag.test(x + y * this->_width))
                std::cout << "1 ";
            else if (this->_player2Diag.test(x + y * this->_width))
                std::cout << "2 ";
            else
                std::cout << "0 ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void Board::printAntiDiagBoard() const{
    for (int y = 0; y < this->_width; y++){
        for (int x = 0; x < this->_width; x++){
            if (this->_player1AntiDiag.test(x + y * this->_width))
                std::cout << "1 ";
            else if (this->_player2AntiDiag.test(x + y * this->_width))
                std::cout << "2 ";
            else
                std::cout << "0 ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void Board::resetBoard(){
    this->_player1.reset();
    this->_player2.reset();
    this->_player1Diag.reset();
    this->_player2Diag.reset();
    this->_player1AntiDiag.reset();
    this->_player2AntiDiag.reset();
}

bool    Board::isPosEmpty(int x, int y) const {
    if (this->_player1.test(x + y * this->_width) || this->_player2.test(x + y * this->_width))
        return false;
    return true;
}

void Board::generateDiagBoard() {
    // _player1Diag.reset();
    // _player2Diag.reset();

    // Perform 45-degree rotation by adjusting row and column mapping
    for (int row = 0; row < this->_width; ++row) {
        for (int col = 0; col < this->_width; ++col) {
            int index = getPos(row, col);
            int newRow = (row + col) % this->_width;
            int newCol = col;
            if (_player1[index])
                _player1Diag.set(newRow + newCol * this->_width);
            else if (_player2[index])
                _player2Diag.set(newRow + newCol * this->_width);
        }
    }
}

void Board::generateAntiDiagBoard() {
    // _player1AntiDiag.reset();
    // _player2AntiDiag.reset();

    // Perform 315-degree rotation by adjusting row and column mapping
    for (int row = 0; row < this->_width; ++row) {
        for (int col = 0; col < this->_width; ++col) {
            int index = getPos(row, col);
            int newRow = (row - col + this->_width) % this->_width;
            int newCol = col;
            if (_player1[index])
                _player1AntiDiag.set(newRow + newCol * this->_width);
            else if (_player2[index])
                _player2AntiDiag.set(newRow + newCol * this->_width);
        }
    }
}

