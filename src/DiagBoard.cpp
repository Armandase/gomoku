#include "../inc/DiagBoard.hpp"
#include "../inc/Pattern.hpp"

DiagBoard::DiagBoard()
    : IBoard()
{
    resetBoard();
}

DiagBoard::~DiagBoard() {

};

DiagBoard::DiagBoard(const DiagBoard& cpy)
    : IBoard::IBoard(cpy)
{
}

DiagBoard& DiagBoard::operator=(const DiagBoard& rhs)
{
    if (this != &rhs) {
        IBoard::operator=(rhs);
    }
    return (*this);
}

uint16_t DiagBoard::convertCoordinate(uint16_t x, uint16_t y) const noexcept
{
    int newY = (x + y) % IBoard::getWidth();
    return (x + newY * IBoard::getWidth());
};

patternBitset DiagBoard::extractPattern(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const
{
    int convertedCoordinate = this->convertCoordinate(xPos, yPos);
    xPos = convertedCoordinate % IBoard::getWidth();
    yPos = convertedCoordinate / IBoard::getWidth();
    int xEnd = xPos + length;

    if (!IBoard::isValidPos(xEnd, yPos) || (xPos < yPos + 1 && xEnd > yPos + 1))
        return patternBitset(0);

    bitboard mask((1ULL << length) - 1);
    bitboard extractedPattern(0);

    if (player == IBoard::getIdPlayer1())
        extractedPattern = IBoard::getPlayer1() & (mask << convertedCoordinate);
    else
        extractedPattern = IBoard::getPlayer2() & (mask << convertedCoordinate);

    extractedPattern >>= convertedCoordinate;

    return patternBitset(extractedPattern.to_ulong());
}

patternBitset DiagBoard::extractPatternReversed(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const
{
    int convertedCoordinate = this->convertCoordinate(xPos, yPos);
    xPos = convertedCoordinate % IBoard::getWidth();
    yPos = convertedCoordinate / IBoard::getWidth();
    int xStart = xPos - length + 1;
    convertedCoordinate = xStart + (yPos * IBoard::getWidth());

    if (!IBoard::isValidPos(xStart, yPos) || (xStart < yPos + 1 && xPos > yPos + 1))
        return patternBitset(0);

    bitboard mask((1ULL << length) - 1);
    bitboard extractedPattern(0);

    if (player == IBoard::getIdPlayer1())
        extractedPattern = IBoard::getPlayer1() & (mask << convertedCoordinate);
    else
        extractedPattern = IBoard::getPlayer2() & (mask << convertedCoordinate);

    extractedPattern >>= convertedCoordinate;

    return patternBitset(extractedPattern.to_ulong());
}

bool DiagBoard::findMatch(uint16_t x, uint16_t y, uint16_t player, bitboard& mask, uint16_t length)
{
    int index = this->convertCoordinate(x, y);
    x = index % IBoard::getWidth();
    y = index / IBoard::getWidth();
    int xEnd = x + length;

    if (!IBoard::isValidPos(xEnd, y) || (x < y + 1 && xEnd > y + 1))
        return false;
        
    if (player == getIdPlayer1()
        && (getPlayer1() & (mask << index)) == (mask << index))
        return true;
    else if (player == getIdPlayer2()
        && (getPlayer2() & (mask << index)) == (mask << index))
        return true;
    return false;
}