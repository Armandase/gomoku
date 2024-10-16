#include "../inc/IBoard.hpp"
#include "../inc/Pattern.hpp"

IBoard::IBoard():
    _player1(0),
    _player2(0),
    _width(BOARD_SIZE + 1),
    _idPlayer1(WHITE),
    _idPlayer2(BLACK)
{
}

IBoard::~IBoard()
{
}

IBoard::IBoard(bitboard& player1, bitboard& player2, uint8_t width, uint8_t idPlayer1, uint8_t idPlayer2):
    _player1(player1),
    _player2(player1),
    _width(width),
    _idPlayer1(idPlayer1),
    _idPlayer2(idPlayer2)
{  
}


IBoard::IBoard(const IBoard &cpy):
    _player1(cpy._player1),
    _player2(cpy._player2),
    _width(cpy._width),
    _idPlayer1(cpy._idPlayer1),
    _idPlayer2(cpy._idPlayer2)
{
}

IBoard &IBoard::operator=(const IBoard &rhs)
{
    if (this != &rhs)
    {
        this->_player1 = rhs._player1;
        this->_player2 = rhs._player2;
    }
    return (*this);
}

// bool IBoard::operator==(const IBoard &a){
//     if (
//         this->_player1 == a._player1 &&
//         this->_player2 == a._player2
//     )
//         return true;
//     return false;
// }


bool IBoard::isValidPos(uint8_t x, uint8_t y) const
{
    if (x < 0 || x >= this->_width || y < 0 || y >= this->_width)
        return false;
    return true;
}


uint8_t IBoard::getWidth() const noexcept{
    return (this->_width);
}

uint8_t IBoard::getIdPlayer1() const noexcept{
    return (this->_idPlayer1);
}

uint8_t IBoard::getIdPlayer2() const noexcept{
    return (this->_idPlayer2);
}


bool    IBoard::isPosEmpty(uint8_t x, uint8_t y) const {
    int convertedCoordinate = this->convertCoordinate(x, y);

    if (this->_player1.test(convertedCoordinate) || this->_player2.test(convertedCoordinate))
        return false;
    return true;
}

void IBoard::setPos(uint8_t x, uint8_t y, int player)
{
    if (this->isValidPos(x, y) == false)
        return ;


    if (this->isPosEmpty(x, y) == false){
        std::cerr << "Error: Invalid move to place stone in (" << x << ";" << y << ")"  << std::endl;
        return ;
    }

    int convertedCoordinate = this->convertCoordinate(x, y);

    if (player == this->_idPlayer1){
        this->_player1.set(convertedCoordinate);
    }
    else if (player == this->_idPlayer2){
        this->_player2.set(convertedCoordinate);
    }
}

void IBoard::removePos(uint8_t x, uint8_t y){
    if (this->isValidPos(x, y) == false)
        return ;
    if (this->isPosEmpty(x, y) == false){
        std::cerr << "Error: Remove an empty stone at (" << x << ";" << y << ")"  << std::endl;
        return ;
    }

    int convertedCoordinate = this->convertCoordinate(x, y);

    if (this->_player1.test(convertedCoordinate)){
        this->_player1.reset(convertedCoordinate);
    } else if (this->_player2.test(convertedCoordinate)){
        this->_player2.reset(convertedCoordinate);
    }
}

uint8_t IBoard::getPos(uint8_t x, uint8_t y) const
{
    if (this->isValidPos(x, y) == false)
        return (0);

    int convertedCoordinate = this->convertCoordinate(x, y);

    if (this->_player1.test(convertedCoordinate))
        return (this->_idPlayer1);
    else if (this->_player2.test(convertedCoordinate))
        return (this->_idPlayer2);  
    else
        return (0);
}

// IBoard::patternMap IBoard::extractPatterns(uint8_t xPos, uint8_t yPos, uint8_t length, int player) const{
//     patternMap result{};
//     bool handleDiag = true;
//     bool handleAntiDiag = true;

//     int xEnd = xPos + length % this->_width;
//     int yEnd = yPos + (length / this->_width);
    
//     if (xEnd > this->_width || yEnd > this->_width){
//         return result;
//     }
//     if (xPos <= yEnd + 1 && xEnd >= yEnd + 1)
//         handleDiag = false;
//     if (this->_width - xPos <= yEnd - 1 && this->_width - xEnd >= yEnd - 1)
//         handleAntiDiag = false;
    

//     int beginDefault = xPos + yPos * this->_width;
//     int beginTranspose = this->coordinateToTranspose1D(xPos, yPos);
//     int beginDiag = this->coordinateToDiag1D(xPos, yPos);
//     int beginAntiDiag = this->coordinateToAntiDiag1D(xPos, yPos);

//     patternBitset defaultBitset(0);
//     patternBitset transposBitset(0);
//     patternBitset diagBitset(0);
//     patternBitset antiDiagBitset(0);
//     for (int i = 0; i < length; ++i) {
//         if (player == this->_idPlayer1){
//             defaultBitset[i] = _player1[beginDefault + i];
//             transposBitset[i] = _player1Transposed[beginTranspose + i];
//             if (handleDiag)
//                 diagBitset[i] = _player1Diag[beginDiag + i];
//             if (handleAntiDiag)
//                 antiDiagBitset[i] = _player1AntiDiag[beginAntiDiag + i];
//         } else {
//             defaultBitset[i] = _player2[beginDefault + i];
//             transposBitset[i] = _player2Transposed[beginTranspose + i];
//             if (handleDiag)
//                 diagBitset[i] = _player1Diag[beginDiag + i];
//             if (handleAntiDiag)
//                 antiDiagBitset[i] = _player1AntiDiag[beginAntiDiag + i];
//         }
//     }
//     result.insert(patternPair(IBoard::PatternType::DEFAULT, defaultBitset));
//     result.insert(patternPair(IBoard::PatternType::TRANSPOS, transposBitset));
//     result.insert(patternPair(IBoard::PatternType::DIAG, diagBitset));
//     result.insert(patternPair(IBoard::PatternType::ANTIDIAG, antiDiagBitset));

//     return result;
// }

// IBoard::patternMap IBoard::extractPatternsReversed(uint8_t xPos, uint8_t yPos, uint8_t length, int player) const{
//     patternMap result{};
//     bool handleDiag = true;
//     bool handleAntiDiag = true;

//     int xEnd = xPos - length % this->_width;
//     int yEnd = yPos - (length / this->_width);
    
//     if (xEnd > this->_width || yEnd > this->_width){
//         return result;
//     }
//     if (xPos <= yEnd + 1 && xEnd >= yEnd + 1)
//         handleDiag = false;
//     if (this->_width - xPos <= yEnd - 1 && this->_width - xEnd >= yEnd - 1)
//         handleAntiDiag = false;
    

//     int beginDefault = xPos + yPos * this->_width;
//     int beginTranspose = this->coordinateToTranspose1D(xPos, yPos);
//     int beginDiag = this->coordinateToDiag1D(xPos, yPos);
//     int beginAntiDiag = this->coordinateToAntiDiag1D(xPos, yPos);

//     patternBitset defaultBitset(0);
//     patternBitset transposBitset(0);
//     patternBitset diagBitset(0);
//     patternBitset antiDiagBitset(0);
//     for (int i = 0; i < length; ++i) {
//         if (player == this->_idPlayer1){
//             defaultBitset[i] = _player1[beginDefault - i];
//             transposBitset[i] = _player1Transposed[beginTranspose - i];
//             if (handleDiag)
//                 diagBitset[i] = _player1Diag[beginDiag - i];
//             if (handleAntiDiag)
//                 antiDiagBitset[i] = _player1AntiDiag[beginAntiDiag - i];
//         } else {
//             defaultBitset[i] = _player2[beginDefault - i];
//             transposBitset[i] = _player2Transposed[beginTranspose - i];
//             if (handleDiag)
//                 diagBitset[i] = _player1Diag[beginDiag - i];
//             if (handleAntiDiag)
//                 antiDiagBitset[i] = _player1AntiDiag[beginAntiDiag - i];
//         }
//     }
//     result.insert(patternPair(IBoard::PatternType::REV_DEFAULT, defaultBitset));
//     result.insert(patternPair(IBoard::PatternType::REV_TRANSPOS, transposBitset));
//     result.insert(patternPair(IBoard::PatternType::REV_DIAG, diagBitset));
//     result.insert(patternPair(IBoard::PatternType::REV_ANTIDIAG, antiDiagBitset));

//     return result;
// }

void IBoard::printBoardX() const
{
    int sliceLen = intlen(this->_width);
    std::cout << "\033[4m"<< std::setw(sliceLen + 1) << "|";
    for (int i = 0; i < this->_width; i++)
        std::cout << std::setw(sliceLen + 1) << i;
    std::cout << "\e[0m" << std::endl;
}


void IBoard::resetBoard(){
    this->_player1.reset();
    this->_player2.reset();
}

// void    IBoard::convertBoard(const IBoardClassic& board){
//     uint16_t convertedCoordiante = 0;
//     uint16_t boardPos = 0;

//     for (int y = 0; y < this->_width; ++y) 
//     {
//         for (int x = 0; x < this->_width; ++x) 
//         {
//             convertedCoordiante = this->convertCoordinate(x, y);
//             if (board.isPosEmpty(x, y) == true){
//                 continue ;
//             }
//             boardPos = board.getPos(x, y);
//             if (boardPos == this->_player1[convertedCoordiante])
//                 this->_player1[convertedCoordiante] = boardPos;
//             else
//                 this->_player2[convertedCoordiante] = boardPos;
//         }
//     }
// }

void IBoard::swapBits(bitboard& board, int pos1, int pos2){
    bool temp = board[pos1];
    board[pos1] = board[pos2];
    board[pos2] = temp;
}


void IBoard::printBoard() const{
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

// void IBoard::checkDiagPattern() {
//     std::bitset<4> patternToCheck;
//     int cnt;
//     for (int row = 0; row < this->_width; ++row) 
//     {
//         cnt = 0;
//         for (int col = 0; col < this->_width; ++col) 
//         {
//             if (col == row + 1) {
//                 patternToCheck.reset();
//                 cnt = 0;
//             }
//             patternToCheck[cnt] = _player1Diag[row + col * this->_width];
//             cnt++;
//             if (cnt == 4) {
//                 std::cout << "CHECK: " << patternToCheck << std::endl;
//                 patternToCheck <<= 1;
//                 cnt = 3;
//             }
//         }
//         std::cout << std::endl;
//     }
// }

// void IBoard::checkAntiDiagPattern() {
//     std::bitset<4> patternToCheck;
//     int cnt;
//     for (int row = 0; row < this->_width; ++row) 
//     {
//         cnt = 0;
//         for (int col = 0; col < this->_width; ++col) 
//         {
//             if (col == this->_width - row) {
//                 patternToCheck.reset();
//                 cnt = 0;
//             }
//             patternToCheck[cnt] = _player1AntiDiag[row + col * this->_width];
//             cnt++;
//             if (cnt == 4) {
//                 std::cout << "CHECK: " << patternToCheck << std::endl;
//                 patternToCheck <<= 1;
//                 cnt = 3;
//             }
//         }
//         std::cout << std::endl;
//     }
// }

// int IBoard::countInDirection(int startRow, int startCol, int rowDelta, int colDelta, int player) {
//     int count = 0;
    
//     for (int d = 1; d < 4; d++) {
//         int newRow = startRow + d * rowDelta;
//         int newCol = startCol + d * colDelta;

//         if (newRow < 0 || newRow >= this->_width || newCol < 0 || newCol >= this->_width)
//             break;

//         if ((player == _idPlayer1 && _player2[newRow * this->_width + newCol])
//         || (player == _idPlayer2 && _player1[newRow * this->_width + newCol]))
//             return -1;
        
//         if ((player == _idPlayer1 && _player1[newRow * this->_width + newCol]) 
//         || (player == _idPlayer2 && _player2[newRow * this->_width + newCol]))
//             count++;
//     }
    
//     return count;
// }

// bool IBoard::checkDoubleThree(int col, int row, int player) {
//     const int   dirX[] = { 0, 0, 1, -1, 1, -1, 1, -1};
//     const int   dirY[] = { 1, -1, 0, 0, 1, -1, -1, 1};
//     int count;
//     int double_three = 0;

//     for (int i = 0; i < 8; i += 2){
//         count = 1;
//         int dirA = countInDirection(row, col, dirX[i], dirY[i], player); 
//         int dirB = countInDirection(row, col, dirX[i + 1], dirY[i + 1], player);
//         if (dirA == 2 && dirB == 2)
//             return true;
//         count += dirA + dirB;
//         if (count == 3)
//             double_three++;
//     }

//     return double_three >= 2;
// }