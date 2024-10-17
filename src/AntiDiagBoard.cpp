#include "../inc/AntiDiagBoard.hpp"
#include "../inc/Pattern.hpp"

AntiDiagBoard::AntiDiagBoard():
    IBoard()
{
    resetBoard();
}

AntiDiagBoard::~AntiDiagBoard(){

};

AntiDiagBoard::AntiDiagBoard(const AntiDiagBoard &cpy):
    IBoard::IBoard(cpy)
{
}

AntiDiagBoard &AntiDiagBoard::operator=(const AntiDiagBoard &rhs)
{
    if (this != &rhs)
    {
	    IBoard::operator=(rhs);
    }
    return (*this);
}

uint16_t  AntiDiagBoard::convertCoordinate(uint16_t x, uint16_t y) const noexcept
{
    int newY = (y - x + IBoard::getWidth()) % IBoard::getWidth();
    return (x + newY * IBoard::getWidth());
};

patternBitset AntiDiagBoard::extractPattern(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const{
    int xEnd = xPos + length % IBoard::getWidth();

    // if (IBoard::isValidPos(xEnd, yPos) == false || (IBoard::getWidth() - xPos < yPos - 1 && IBoard::getWidth() - xEnd > yPos - 1))
    if (IBoard::isValidPos(xEnd, yPos) == false)
        return patternBitset(0);

    int convertedCoordinate = this->convertCoordinate(xPos, yPos);

    bitboard mask((1 << length) - 1);
    bitboard extractedPattern(0);
    if (player == IBoard::getIdPlayer1())
        extractedPattern = IBoard::getPlayer1() &  (mask << convertedCoordinate);
    else
        extractedPattern = IBoard::getPlayer2() &  (mask << convertedCoordinate);
    extractedPattern >>= convertedCoordinate;
    return patternBitset(extractedPattern.to_ulong());
}

patternBitset AntiDiagBoard::extractPatternReversed(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const{
    int xEnd = xPos - length % getWidth();

    // if (isValidPos(xEnd, yPos) == false || (IBoard::getWidth() - xEnd < yPos - 1 && IBoard::getWidth() - xPos > yPos - 1))
    if (isValidPos(xEnd, yPos) == false)
        return patternBitset(0);

    int convertedCoordinate = this->convertCoordinate(xEnd + 1, yPos);

    bitboard mask((1 << length) - 1);
    bitboard extractedPattern(0);
    if (player == getIdPlayer1())
        extractedPattern = getPlayer1() &  (mask << convertedCoordinate);
    else
        extractedPattern = getPlayer2() &  (mask << convertedCoordinate);
    extractedPattern >>= convertedCoordinate;
    return patternBitset(extractedPattern.to_ulong());
}