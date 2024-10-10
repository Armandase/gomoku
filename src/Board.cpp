#include "../inc/Board.hpp"
#include "../inc/Pattern.hpp"

Board::Board():
    _player1(),
    _player2(),
    _player1Transposed(),
    _player2Transposed(),
    _player1Diag(),
    _player2Diag(),
    _player1AntiDiag(),
    _player2AntiDiag(),
    _player1Capture(0),
    _player2Capture(0),
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
    _player1Capture(cpy._player1Capture),
    _player2Capture(cpy._player2Capture),
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
        this->_player1Capture = rhs._player1Capture;
        this->_player2Capture = rhs._player2Capture;
        this->_idPlayer1 = rhs._idPlayer1;
        this->_idPlayer2 = rhs._idPlayer2;
    }
    return (*this);
}

bool Board::isValidPos(int x, int y)
{
    if (x < 0 || x > this->_width || y < 0 || y > this->_width)
        return false;
    return true;
}

int Board::getCapture(int player) {
    if (player == this->_idPlayer1)
        return _player1Capture;
    else if (player == this->_idPlayer2)
        return _player2Capture;
    return 0;
}

void Board::addCapture(int player) {
    if (player == this->_idPlayer1)
        _player1Capture++;
    else if (player == this->_idPlayer2)
        _player2Capture++;
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
    int newY = (x + y) % this->_width;
    // return (newRow + y * this->_width);
    return (x + newY * this->_width);
}

int Board::coordinateToAntiDiag1D(int x, int y) const
{
    int newY = (y - x + this->_width) % this->_width;
    return (x + newY * this->_width);
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

Board::patternMap Board::extractPatterns(int xPos, int yPos, int length, int player) const{
    patternMap result{};
    bool handleDiag = true;
    bool handleAntiDiag = true;

    int xEnd = xPos + length % this->_width;
    int yEnd = yPos + (length / this->_width);
    
    if (xEnd > this->_width || yEnd > this->_width){
        return result;
    }
    if (xPos <= yEnd + 1 && xEnd >= yEnd + 1)
        handleDiag = false;
    if (this->_width - xPos <= yEnd - 1 && this->_width - xEnd >= yEnd - 1)
        handleAntiDiag = false;
    

    int beginDefault = xPos + yPos * this->_width;
    int beginTranspose = this->coordinateToTranspose1D(xPos, yPos);
    int beginDiag = this->coordinateToDiag1D(xPos, yPos);
    int beginAntiDiag = this->coordinateToAntiDiag1D(xPos, yPos);

    patternBitset defaultBitset;
    patternBitset transposBitset;
    patternBitset diagBitset;
    patternBitset antiDiagBitset;
    for (int i = 0; i < length; ++i) {
        if (player == this->_idPlayer1){
            defaultBitset[i] = _player1[beginDefault + i];
            transposBitset[i] = _player1Transposed[beginTranspose + i];
            if (handleDiag)
                diagBitset[i] = _player1Diag[beginDiag + i];
            if (handleAntiDiag)
                antiDiagBitset[i] = _player1AntiDiag[beginAntiDiag + i];
        } else {
            defaultBitset[i] = _player2[beginDefault + i];
            transposBitset[i] = _player2Transposed[beginTranspose + i];
            if (handleDiag)
                diagBitset[i] = _player1Diag[beginDiag + i];
            if (handleAntiDiag)
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
    for (int y = 0; y < this->_width; ++y) 
    {
        for (int x = 0; x < this->_width; ++x) 
        {
            int newY = (y + x) % this->_width;
            int newX = x;
            _player1Diag[newX + newY * this->_width] = _player1[x + y * this->_width];
            _player2Diag[newX + newY * this->_width] = _player2[x + y * this->_width];
        }
    }
}

void Board::generateAntiDiagBoard() {
    for (int y = 0; y < this->_width; ++y) 
    {
        for (int x = 0; x < this->_width; ++x) 
        {
            int newY = (y - x + this->_width) % this->_width;
            int newX = x;
            _player1AntiDiag[newX + newY * this->_width] = _player1[x + y * this->_width];
            _player2AntiDiag[newX + newY * this->_width] = _player2[x + y * this->_width];
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

int Board::countInDirection(int startRow, int startCol, int rowDelta, int colDelta, int player) {
    int count = 0;
    
    for (int d = 1; d < 4; d++) {
        int newRow = startRow + d * rowDelta;
        int newCol = startCol + d * colDelta;

        if (newRow < 0 || newRow >= this->_width || newCol < 0 || newCol >= this->_width)
            break;

        if ((player == _idPlayer1 && _player2[newRow * this->_width + newCol])
        || (player == _idPlayer2 && _player1[newRow * this->_width + newCol]))
            return -1;
        
        if ((player == _idPlayer1 && _player1[newRow * this->_width + newCol]) 
        || (player == _idPlayer2 && _player2[newRow * this->_width + newCol]))
            count++;
    }
    
    return count;
}

bool Board::checkDoubleThree(int col, int row, int player) {
    const int   dirX[] = { 0, 0, 1, -1, 1, -1, 1, -1};
    const int   dirY[] = { 1, -1, 0, 0, 1, -1, -1, 1};
    int count;
    int double_three = 0;

    for (int i = 0; i < 8; i += 2){
        count = 1;
        int dirA = countInDirection(row, col, dirX[i], dirY[i], player); 
        int dirB = countInDirection(row, col, dirX[i + 1], dirY[i + 1], player);
        if (dirA == 2 && dirB == 2)
            return true;
        count += dirA + dirB;
        if (count == 3)
            double_three++;
    }

    return double_three >= 2;
}