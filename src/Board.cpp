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
    int coordinateToTranspose1d = this->coordinateToTranspose1D(x, y);
    int coordinateToDiag1d = this->coordinateToDiag1D(x, y);
    int coordinateToAntiDiag1d = this->coordinateToAntiDiag1D(x, y);

    if (player == this->_idPlayer1 && !this->_player2.test(x + y * this->_width)){
        this->_player1.set(x + y * this->_width);
        this->_player1Transposed.set(coordinateToTranspose1d);
        this->_player1Diag.set(coordinateToDiag1d);
        this->_player1AntiDiag.set(coordinateToAntiDiag1d);
    }
    else if (player == this->_idPlayer2 && !this->_player1.test(x + y * this->_width)){
        this->_player2.set(x + y * this->_width);
        this->_player2Transposed.set(coordinateToTranspose1d);
        this->_player2Diag.set(coordinateToDiag1d);
        this->_player2AntiDiag.set(coordinateToAntiDiag1d);
    }
    else{
        std::cerr << "Error: Invalid player ID" << std::endl;
        return ;
    }
}

int Board::coordinateToTranspose1D(int x, int y) const
{
    return (y + x * this->_width);
}

int Board::coordinateToDiag1D(int x, int y) const
{
    int newRow = (x + y) % this->_width;
    // return (newRow + y * this->_width);
    return (newRow + x * this->_width);
}

int Board::coordinateToAntiDiag1D(int x, int y) const
{
    int newRow = (x - y + this->_width) % this->_width;
    return (newRow + y * this->_width);
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
    int beginDefault = xStart + yStart * this->_width;
    int beginTranspose = this->coordinateToTranspose1D(xStart, yStart);
    int beginDiag = this->coordinateToDiag1D(xStart, yStart);
    std::cout << "Begin diag:" << beginDiag << std::endl;
    int beginAntiDiag = this->coordinateToAntiDiag1D(xStart, yStart);
    // int beginDefault = xStart + yStart * this->_width;
    int nbIter = (xEnd + yEnd * this->_width) - beginDefault;

    patternBitset defaultBitset;
    patternBitset transposBitset;
    patternBitset diagBitset;
    patternBitset antiDiagBitset;
    for (int i = 0; i < nbIter; ++i) {
        if (player == this->_idPlayer1){
            defaultBitset[i] = _player1[beginDefault + i];
            transposBitset[i] = _player1Transposed[beginTranspose + i];
            diagBitset[i] = _player1Diag[beginDiag + i];
            antiDiagBitset[i] = _player1AntiDiag[beginAntiDiag + i];
        } else {
            defaultBitset[i] = _player2[beginDefault + i];
            transposBitset[i] = _player2Transposed[beginTranspose + i];
            diagBitset[i] = _player1Diag[beginDiag + i];
            antiDiagBitset[i] = _player1AntiDiag[beginAntiDiag + i];
        }
    }
    result.insert(patternPair(Board::PatternType::DEFAULT, defaultBitset));
    result.insert(patternPair(Board::PatternType::TRANSPOS, transposBitset));
    result.insert(patternPair(Board::PatternType::DIAG, diagBitset));
    result.insert(patternPair(Board::PatternType::ANTIDIAG, antiDiagBitset));

    return result;
}

void Board::printBoardX() const
{
    int sliceLen = intlen(this->_width);
    std::cout << "\033[4m"<< std::setw(sliceLen + 1) << "|";
    for (int i = 0; i < this->_width; i++)
        std::cout << std::setw(sliceLen + 1) << i;
    std::cout << "\e[0m" << std::endl;
}

void Board::printBoard() const{
    printBoardX();
    int sliceLen = intlen(this->_width);
    for (int y = 0; y < this->_width; y++)
    {
        std::cout << std::setw(sliceLen) << y << "|";
        for (int x = 0; x < this->_width; x++)
        {
            if (this->_player1.test(x + y * this->_width))
                std::cout << std::setw(sliceLen + 1) << "1";
            else if (this->_player2.test(x + y * this->_width))
                std::cout << std::setw(sliceLen + 1) << "2";
            else
                std::cout << std::setw(sliceLen + 1) << "0";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void Board::printDiagBoard() const{
    printBoardX();
    int sliceLen = intlen(this->_width);
    for (int y = 0; y < this->_width; y++)
    {
        std::cout << std::setw(sliceLen) << y << "|";
        for (int x = 0; x < this->_width; x++)
        {
            if (this->_player1Diag.test(x + y * this->_width))
                std::cout << std::setw(sliceLen + 1) << "1";
            else if (this->_player2Diag.test(x + y * this->_width))
                std::cout << std::setw(sliceLen + 1) << "2";
            else
                std::cout << std::setw(sliceLen + 1) << "0";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void Board::printAntiDiagBoard() const{
    printBoardX();
    int sliceLen = intlen(this->_width);
    for (int y = 0; y < this->_width; y++)
    {
        std::cout << std::setw(sliceLen) << y << "|";
        for (int x = 0; x < this->_width; x++)
        {
            if (this->_player1AntiDiag.test(x + y * this->_width))
                std::cout << std::setw(sliceLen + 1) << "1";
            else if (this->_player2AntiDiag.test(x + y * this->_width))
                std::cout << std::setw(sliceLen + 1) << "2";
            else
                std::cout << std::setw(sliceLen + 1) << "0";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void    Board::printTransposedBoard() const
{
    printBoardX();
    int sliceLen = intlen(this->_width);
    for (int y = 0; y < this->_width; y++)
    {
        std::cout << std::setw(sliceLen) << y << "|";
        for (int x = 0; x < this->_width; x++)
        {
            if (this->_player1Transposed.test(x + y * this->_width))
                std::cout << std::setw(sliceLen + 1) << "1";
            else if (this->_player2Transposed.test(x + y * this->_width))
                std::cout << std::setw(sliceLen + 1) << "2";
            else
                std::cout << std::setw(sliceLen + 1) << "0";
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
    for (int row = 0; row < this->_width; ++row) 
    {
        for (int col = 0; col < this->_width; ++col) 
        {
            int newRow = (row + col) % this->_width;
            int newCol = col;
            // _player1Diag[newRow + newCol * this->_width] = _player1[row + col * this->_width];
            // _player2Diag[newRow + newCol * this->_width] = _player2[row + col * this->_width];
            _player1Diag[newRow + newCol * this->_width] = _player1[col + row * this->_width];
            _player2Diag[newRow + newCol * this->_width] = _player2[col + row * this->_width];
        }
    }
}

void Board::generateAntiDiagBoard() {
    for (int row = 0; row < this->_width; ++row) 
    {
        for (int col = 0; col < this->_width; ++col) 
        {
            int newRow = (row - col + this->_width) % this->_width;
            int newCol = col;
            // _player1AntiDiag[newRow + newCol * this->_width] = _player1[row + col * this->_width];
            // _player2AntiDiag[newRow + newCol * this->_width] = _player2[row + col * this->_width];
            _player1AntiDiag[newRow + newCol * this->_width] = _player1[col + row * this->_width];
            _player2AntiDiag[newRow + newCol * this->_width] = _player2[col + row * this->_width];
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

void Board::checkDiagPattern() {
    std::bitset<4> patternToCheck;
    int cnt;
    for (int row = 0; row < this->_width; ++row) 
    {
        cnt = 0;
        for (int col = 0; col < this->_width; ++col) 
        {
            if (col == row + 1) {
                patternToCheck.reset();
                cnt = 0;
            }
            patternToCheck[cnt] = _player1Diag[row + col * this->_width];
            cnt++;
            if (cnt == 4) {
                std::cout << "CHECK: " << patternToCheck << std::endl;
                patternToCheck <<= 1;
                cnt = 3;
            }
        }
        std::cout << std::endl;
    }
}

void Board::checkAntiDiagPattern() {
    std::bitset<4> patternToCheck;
    int cnt;
    for (int row = 0; row < this->_width; ++row) 
    {
        cnt = 0;
        for (int col = 0; col < this->_width; ++col) 
        {
            if (col == this->_width - row) {
                patternToCheck.reset();
                cnt = 0;
            }
            patternToCheck[cnt] = _player1AntiDiag[row + col * this->_width];
            cnt++;
            if (cnt == 4) {
                std::cout << "CHECK: " << patternToCheck << std::endl;
                patternToCheck <<= 1;
                cnt = 3;
            }
        }
        std::cout << std::endl;
    }
}
