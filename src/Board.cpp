#include "../inc/Board.hpp"

Board::Board():
    _player1(),
    _player2(),
    _idPlayer1(WHITE),
    _idPlayer2(BLACK)
{
    resetBoard();
}

Board::~Board(){

};

Board::Board(const Board &cpy):
    _player1(cpy._player1),
    _player2(cpy._player2),
    _width(cpy._width),
    _idPlayer1(cpy._idPlayer1),
    _idPlayer2(cpy._idPlayer2)
{
    generateTransposedBoard();
}

Board &Board::operator=(const Board &rhs)
{
    if (this != &rhs)
    {
        this->_player1 = rhs._player1;
        this->_player2 = rhs._player2;
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

void    Board::printTransposedBoard() const{
    for (int y = 0; y < this->_width; y++){
        for (int x = 0; x < this->_width; x++){
            if (this->_player1Transposed.test(x + y * this->_width))
                std::cout << "1 ";
            else if (this->_player2Transposed.test(x + y * this->_width))
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
}

bool    Board::isPosEmpty(int x, int y) const {
    if (this->_player1.test(x + y * this->_width) || this->_player2.test(x + y * this->_width))
        return false;
    return true;
}

void Board::swapBits(bitboard& board, int pos1, int pos2){
    bool temp = board[pos1];
    board[pos1] = board[pos2];
    board[pos2] = temp;
}

void Board::generateTransposedBoard(){
    if (this->_player1.none() == true && this->_player2.none() == true)
    {
        std::cout << __FUNCTION__ << " Transpose an empty board" << std::endl;
    }
    this->_player1Transposed = this->_player1;
    this->_player2Transposed = this->_player2;

    int n = std::sqrt(this->_player1.size());
    for(int i = 0; i < n; ++i){
        for(int j = i+1; j < n; ++j){
            swapBits(_player1Transposed, n*i + j, n*j + i);
            swapBits(_player2Transposed, n*i + j, n*j + i);
        }
    }
}
