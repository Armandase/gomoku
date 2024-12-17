#include "../inc/AntiDiagBoard.hpp"

AntiDiagBoard::AntiDiagBoard()
    : IBoard()
{
    resetBoard();
}

AntiDiagBoard::~AntiDiagBoard() {

};

AntiDiagBoard::AntiDiagBoard(const AntiDiagBoard& cpy)
    : IBoard::IBoard(cpy)
{
}

AntiDiagBoard& AntiDiagBoard::operator=(const AntiDiagBoard& rhs)
{
    if (this != &rhs) {
        IBoard::operator=(rhs);
    }
    return (*this);
}

uint16_t AntiDiagBoard::convertCoordinate(uint16_t x, uint16_t y) const noexcept
{
    int newY = (y - x + IBoard::getWidth()) % IBoard::getWidth();
    return (x + newY * IBoard::getWidth());
};

patternBitset AntiDiagBoard::extractPattern(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const
{
    int convertedCoordinate = this->convertCoordinate(xPos, yPos);
    xPos = convertedCoordinate % IBoard::getWidth();
    yPos = convertedCoordinate / IBoard::getWidth();
    int xEnd = xPos + length - 1;

    if (!IBoard::isValidPos(xEnd, yPos) || (IBoard::getWidth() - xPos < yPos + 1 && IBoard::getWidth() - xEnd > yPos + 1)) {
        return patternBitset(0);
    }

    bitboard mask((1ULL << length) - 1);
    bitboard extractedPattern(0);

    if (player == IBoard::getIdPlayer1())
        extractedPattern = IBoard::getPlayer1() & (mask << convertedCoordinate);
    else
        extractedPattern = IBoard::getPlayer2() & (mask << convertedCoordinate);

    extractedPattern >>= convertedCoordinate;

    return patternBitset(extractedPattern.to_ulong());
}

patternBitset AntiDiagBoard::extractPatternReversed(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const
{
    int convertedCoordinate = this->convertCoordinate(xPos, yPos);
    xPos = convertedCoordinate % IBoard::getWidth();
    yPos = convertedCoordinate / IBoard::getWidth();
    int xStart = xPos - length + 1;
    convertedCoordinate = xStart + (yPos * IBoard::getWidth());

    if (!IBoard::isValidPos(xStart, yPos) || (IBoard::getWidth() - xStart < yPos + 1 && IBoard::getWidth() - xPos > yPos + 1)) {
        return patternBitset(0);
    }

    bitboard mask((1ULL << length) - 1);
    bitboard extractedPattern(0);

    if (player == IBoard::getIdPlayer1())
        extractedPattern = IBoard::getPlayer1() & (mask << convertedCoordinate);
    else
        extractedPattern = IBoard::getPlayer2() & (mask << convertedCoordinate);

    extractedPattern >>= convertedCoordinate;

    return patternBitset(extractedPattern.to_ulong());
}

bool AntiDiagBoard::findMatch(uint16_t x, uint16_t y, uint16_t player, bitboard& mask, uint16_t length)
{
    int index = this->convertCoordinate(x, y);
    x = index % IBoard::getWidth();
    y = index / IBoard::getWidth();
    int xEnd = x + length - 1;

    if (!IBoard::isValidPos(xEnd, y) || (IBoard::getWidth() - x < y + 1 && IBoard::getWidth() - xEnd > y + 1))
        return false;

    if (player == getIdPlayer1()
        && (getPlayer1() & (mask << index)) == (mask << index))
        return true;
    else if (player == getIdPlayer2()
        && (getPlayer2() & (mask << index)) == (mask << index))
        return true;
    return false;
}