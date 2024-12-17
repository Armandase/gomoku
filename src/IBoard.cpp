#include "../inc/IBoard.hpp"

IBoard::IBoard()
    : _player1(0)
    , _player2(0)
    , _width(BOARD_SIZE)
    , _idPlayer1(WHITE)
    , _idPlayer2(BLACK)
{
    resetBoard();
}

IBoard::~IBoard()
{
}

IBoard::IBoard(bitboard& player1, bitboard& player2, uint16_t width, uint16_t idPlayer1, uint16_t idPlayer2)
    : _player1(player1)
    , _player2(player2)
    , _width(width)
    , _idPlayer1(idPlayer1)
    , _idPlayer2(idPlayer2)
{
}

IBoard::IBoard(const IBoard& cpy)
    : _player1(cpy._player1)
    , _player2(cpy._player2)
    , _width(cpy._width)
    , _idPlayer1(cpy._idPlayer1)
    , _idPlayer2(cpy._idPlayer2)
{
}

IBoard& IBoard::operator=(const IBoard& rhs)
{
    if (this != &rhs) {
        this->_player1 = rhs._player1;
        this->_player2 = rhs._player2;
    }
    return (*this);
}

bool IBoard::operator==(const IBoard& rhs)
{
    if (
        this->_player1 == rhs._player1 && this->_player2 == rhs._player2)
        return true;
    return false;
}

bool IBoard::isValidPos(uint16_t x, uint16_t y) const
{
    if (x < 0 || x >= this->_width || y < 0 || y >= this->_width)
        return false;
    return true;
}

uint16_t IBoard::getWidth() const noexcept
{
    return (this->_width);
}

uint16_t IBoard::getIdPlayer1() const noexcept
{
    return (this->_idPlayer1);
}

uint16_t IBoard::getIdPlayer2() const noexcept
{
    return (this->_idPlayer2);
}

bool IBoard::isPosEmpty(uint16_t x, uint16_t y) const
{
    if (this->isValidPos(x, y) == false)
        return false;
    const int coor = x + y * this->_width;
    if (this->_player1.test(coor) || this->_player2.test(coor))
        return false;
    return true;
}

void IBoard::setPos(uint16_t x, uint16_t y, int player)
{
    if (this->isValidPos(x, y) == false)
        return;

    const int convertedCoordinate = this->convertCoordinate(x, y);
    x = convertedCoordinate % this->_width;
    y = convertedCoordinate / this->_width;
    if (this->isPosEmpty(x, y) == false) {
        std::cerr << "Error: Position already use in (" << x << ";" << y << ")" << std::endl;
        return;
    }

    if (player == this->_idPlayer1) {
        this->_player1.set(convertedCoordinate);
    } else if (player == this->_idPlayer2) {
        this->_player2.set(convertedCoordinate);
    }
}

void IBoard::removePos(uint16_t x, uint16_t y)
{
    if (this->isValidPos(x, y) == false)
        return;

    const int convertedCoordinate = this->convertCoordinate(x, y);
    x = convertedCoordinate % this->_width;
    y = convertedCoordinate / this->_width;

    if (this->isPosEmpty(x, y) == true) {
        std::cerr << "Error: Remove an empty stone at (" << x << ";" << y << ")" << std::endl;
        return;
    }

    if (this->_player1.test(convertedCoordinate)) {
        this->_player1.reset(convertedCoordinate);
    } else if (this->_player2.test(convertedCoordinate)) {
        this->_player2.reset(convertedCoordinate);
    }
}

uint16_t IBoard::getPos(uint16_t x, uint16_t y) const
{
    if (this->isValidPos(x, y) == false)
        return (0);

    const int convertedCoordinate = this->convertCoordinate(x, y);

    if (this->_player1.test(convertedCoordinate))
        return (this->_idPlayer1);
    else if (this->_player2.test(convertedCoordinate))
        return (this->_idPlayer2);
    else
        return (0);
}

IBoard::bitboard IBoard::getPlayer1() const noexcept
{
    return (this->_player1);
}

IBoard::bitboard IBoard::getPlayer2() const noexcept
{
    return (this->_player2);
}

void IBoard::printBoardX() const
{
    const int sliceLen = intlen(this->_width);
    std::cout << "\033[4m" << std::setw(sliceLen + 1) << "|";
    for (int i = 0; i < this->_width; i++)
        std::cout << std::setw(sliceLen + 1) << i;
    std::cout << "\e[0m" << std::endl;
}

void IBoard::resetBoard()
{
    this->_player1.reset();
    this->_player2.reset();
}

void IBoard::swapBits(bitboard& board, int pos1, int pos2)
{
    bool temp = board[pos1];
    board[pos1] = board[pos2];
    board[pos2] = temp;
}

bool IBoard::findMatch(uint16_t x, uint16_t y, uint16_t player, bitboard& mask, uint16_t length)
{
    (void)length;
    const int index = this->convertCoordinate(x, y);
    if (player == getIdPlayer1() && (_player1 & (mask << index)) == (mask << index))
        return true;
    if (player == getIdPlayer2() && (_player2 & (mask << index)) == (mask << index))
        return true;
    return false;
}

void IBoard::printBoard() const
{
    printBoardX();
    const int sliceLen = intlen(this->_width);
    for (int y = 0; y < this->_width; y++) {
        std::cout << std::setw(sliceLen) << y << "|";
        for (int x = 0; x < this->_width; x++) {
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