#include "../inc/TransposedBoard.hpp"

TransposedBoard::TransposedBoard()
    : IBoard()
{
    resetBoard();
}

TransposedBoard::~TransposedBoard() {

};

TransposedBoard::TransposedBoard(const TransposedBoard& cpy)
    : IBoard::IBoard(cpy)
{
}

TransposedBoard& TransposedBoard::operator=(const TransposedBoard& rhs)
{
    if (this != &rhs) {
        IBoard::operator=(rhs);
    }
    return (*this);
}

uint16_t TransposedBoard::convertCoordinate(uint16_t x, uint16_t y) const noexcept
{
    return (y + x * IBoard::getWidth());
};

patternBitset TransposedBoard::extractPattern(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const
{
    int convertedCoordinate = this->convertCoordinate(xPos, yPos);
    xPos = convertedCoordinate % IBoard::getWidth();
    yPos = convertedCoordinate / IBoard::getWidth();
    int xEnd = xPos + length;

    if (IBoard::isValidPos(xEnd, yPos) == false)
        return patternBitset(0);

    bitboard mask((1 << length) - 1);
    bitboard extractedPattern(0);
    if (player == IBoard::getIdPlayer1())
        extractedPattern = IBoard::getPlayer1() & (mask << convertedCoordinate);
    else
        extractedPattern = IBoard::getPlayer2() & (mask << convertedCoordinate);

    extractedPattern >>= convertedCoordinate;
    return patternBitset(extractedPattern.to_ulong());
}

patternBitset TransposedBoard::extractPatternReversed(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const
{
    int convertedCoordinate = this->convertCoordinate(xPos, yPos);
    xPos = convertedCoordinate % IBoard::getWidth();
    yPos = convertedCoordinate / IBoard::getWidth();
    int xStart = xPos - length + 1;
    convertedCoordinate = xStart + (yPos * IBoard::getWidth());

    if (IBoard::isValidPos(xStart, yPos) == false)
        return patternBitset(0);

    bitboard mask((1 << length) - 1);
    bitboard extractedPattern(0);
    if (player == getIdPlayer1())
        extractedPattern = getPlayer1() & (mask << convertedCoordinate);
    else
        extractedPattern = getPlayer2() & (mask << convertedCoordinate);

    extractedPattern >>= convertedCoordinate;
    return patternBitset(extractedPattern.to_ulong());
}
