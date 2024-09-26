#include "../inc/Board.hpp"
#include "../inc/Pattern.hpp"

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
    _player1Transposed(cpy._player1Transposed),
    _player2Transposed(cpy._player2Transposed),
    _player1Diag(cpy._player1Diag),
    _player2Diag(cpy._player2Diag),
    _player1AntiDiag(cpy._player1AntiDiag),
    _player2AntiDiag(cpy._player2AntiDiag),
    _width(cpy._width),
    _idPlayer1(cpy._idPlayer1),
    _idPlayer2(cpy._idPlayer2)
{
    generateDiagBoard();
    generateAntiDiagBoard();
    generateTransposedBoard();
    // std::cout << "ORIGINAL" << std::endl;
    // printBoard();
    // std::cout << "TRANSPOSED BOARD" << std::endl;
    // printTransposedBoard();    
    // std::cout << "DIAG" << std::endl;
    // printDiagBoard();
    // std::cout << "ANTI DIAG" << std::endl;
    // printAntiDiagBoard();
}

Board &Board::operator=(const Board &rhs)
{
    if (this != &rhs)
    {
        this->_player1 = rhs._player1;
        this->_player2 = rhs._player2;
        this->_player1Transposed = rhs._player1Transposed;
        this->_player2Transposed = rhs._player2Transposed;
        this->_player1Diag = rhs._player1Diag;
        this->_player2Diag = rhs._player2Diag;
        this->_player1AntiDiag = rhs._player1AntiDiag;
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

Board::patternMap Board::extractPatterns(int xStart, int yStart, int xEnd, int yEnd, int player) const{
    patternMap result{};

    if (xEnd > this->_width || yEnd > this->_width){
        return result;
    }
        // return de facon clean 
        // return (Pattern::patternBitset().reset());
    // xEnd = this->_width - xEnd; 
    // yEnd = this->_width - yEnd; 
    // xStart = this->_width - xStart; 
    // yStart = this->_width - yStart; 
    // printBoard();
    std::cout << "start x: " << xStart << " y: " << yStart << std::endl;
    std::cout << "end x: " << xEnd << " y: " << yEnd << std::endl;
    int begin = xStart + yStart * this->_width;
    int end = xEnd + yEnd * this->_width;


    patternBitset defaultBitset;
    patternBitset transposBitset;
    for (int i = begin; i < begin - end + 1; ++i) {
        if (player == this->_idPlayer1){
            defaultBitset[i] = _player1[begin + i];
            transposBitset[i] = _player1Transposed[begin + i];
        } else {
            defaultBitset[i] = _player2[begin + i];
            transposBitset[i] = _player2Transposed[begin + i];
        }
    }

    result.insert(patternPair(Board::PatternType::DEFAULT, defaultBitset));
    result.insert(patternPair(Board::PatternType::TRANSPOS, transposBitset));

    return result;
}

void Board::printBoard() const{
    for (int y = 0; y < this->_width; y++){
        for (int x = 0; x < this->_width; x++){
            if (this->_player1.test(x + y * this->_width))
                std::cout << "1  ";
            else if (this->_player2.test(x + y * this->_width))
                std::cout << "2  ";
            else
                std::cout << "0  ";
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

void Board::generateDiagBoard() {
    // _player1Diag.reset();
    // _player2Diag.reset();

    // Perform 45-degree rotation by adjusting row and column mapping
    for (int row = 0; row < this->_width; ++row) {
        for (int col = 0; col < this->_width; ++col) {
            int newRow = (row + col) % this->_width;
            int newCol = col;
            _player1Diag[newRow + newCol * this->_width] = _player1[row + col * this->_width];
            _player2Diag[newRow + newCol * this->_width] = _player2[row + col * this->_width];
        }
    }
}

void Board::generateAntiDiagBoard() {
    // _player1AntiDiag.reset();
    // _player2AntiDiag.reset();

    // Perform 315-degree rotation by adjusting row and column mapping
    for (int row = 0; row < this->_width; ++row) {
        for (int col = 0; col < this->_width; ++col) {
            int newRow = (row - col + this->_width) % this->_width;
            int newCol = col;
            _player1AntiDiag[newRow + newCol * this->_width] = _player1[row + col * this->_width];
            _player2AntiDiag[newRow + newCol * this->_width] = _player2[row + col * this->_width];
        }
    }
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