#include "../inc/IBoard.hpp"
#include "../inc/Pattern.hpp"

IBoard::IBoard():
    _player1(),
    _player2(),
    _width(BOARD_SIZE + 1),
    _idPlayer1(WHITE),
    _idPlayer2(BLACK)
{
    resetBoard();
}

IBoard::~IBoard()
{
}

IBoard::IBoard(bitboard& player1, bitboard& player2, uint16_t width, uint16_t idPlayer1, uint16_t idPlayer2):
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


bool IBoard::isValidPos(uint16_t x, uint16_t y) const
{
    if (x < 0 || x >= this->_width || y < 0 || y >= this->_width)
        return false;
    return true;
}


uint16_t IBoard::getWidth() const noexcept{
    return (this->_width);
}

uint16_t IBoard::getIdPlayer1() const noexcept{
    return (this->_idPlayer1);
}

uint16_t IBoard::getIdPlayer2() const noexcept{
    return (this->_idPlayer2);
}


bool    IBoard::isPosEmpty(uint16_t x, uint16_t y) const {
    int convertedCoordinate = this->convertCoordinate(x, y);

    if (this->_player1.test(convertedCoordinate) || this->_player2.test(convertedCoordinate))
        return false;
    return true;
}

void IBoard::setPos(uint16_t x, uint16_t y, int player)
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

void IBoard::removePos(uint16_t x, uint16_t y){
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

uint16_t IBoard::getPos(uint16_t x, uint16_t y) const
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

IBoard::bitboard IBoard::getPlayer1() const noexcept{
    return (this->_player1);
}

IBoard::bitboard IBoard::getPlayer2() const noexcept{
    return (this->_player2);
}

patternBitset IBoard::extractPattern(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const{
    int xEnd = xPos + length % getWidth();
    int yEnd = yPos + (length / getWidth());

    if (isValidPos(xEnd, yEnd) == false)
        return patternBitset(0);

    int convertedCoordinate = this->convertCoordinate(xPos, yPos);

    bitboard mask("1111");
    bitboard extractedPattern(0);
    if (player == getIdPlayer1())
        extractedPattern = getPlayer1() &  (mask << convertedCoordinate);
    else
        extractedPattern = getPlayer2() &  (mask << convertedCoordinate);
    extractedPattern >>= convertedCoordinate;
    return patternBitset(extractedPattern.to_ulong());
}

patternBitset IBoard::extractPatternReversed(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const{
    int xEnd = xPos - length % getWidth();
    int yEnd = yPos - (length / getWidth());

    if (isValidPos(xEnd, yEnd) == false)
        return patternBitset(0);

    int convertedCoordinate = this->convertCoordinate(xEnd, yEnd);

    bitboard mask("1111");
    bitboard extractedPattern(0);
    if (player == getIdPlayer1())
        extractedPattern = getPlayer1() &  (mask << convertedCoordinate);
    else
        extractedPattern = getPlayer2() &  (mask << convertedCoordinate);
    extractedPattern >>= convertedCoordinate;
    return patternBitset(extractedPattern.to_ulong());
}

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