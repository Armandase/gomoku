#include "../inc/DiagBoard.hpp"
#include "../inc/Pattern.hpp"

DiagBoard::DiagBoard():
    IBoard()
{
    resetBoard();
}

DiagBoard::~DiagBoard(){

};

DiagBoard::DiagBoard(const DiagBoard &cpy):
    IBoard::IBoard(cpy)
{
}

DiagBoard &DiagBoard::operator=(const DiagBoard &rhs)
{
    if (this != &rhs)
    {
	    IBoard::operator=(rhs);
    }
    return (*this);
}

uint16_t  DiagBoard::convertCoordinate(uint16_t x, uint16_t y) const noexcept
{
    int newY = (x + y) % IBoard::getWidth();
    return (x + newY * IBoard::getWidth());
};

patternBitset DiagBoard::extractPattern(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const{
    int xEnd = xPos + length % IBoard::getWidth();
    int yEnd = yPos + (length / IBoard::getWidth());

    if (IBoard::isValidPos(xEnd, yEnd) == false || (xPos < yEnd + 1 && xEnd > yEnd + 1))
        return patternBitset(0);
    
    int convertedCoordinate = this->convertCoordinate(xPos, yPos);

    bitboard mask("1111");
    bitboard extractedPattern(0);
    if (player == IBoard::getIdPlayer1())
        extractedPattern = IBoard::getPlayer1() &  (mask << convertedCoordinate);
    else
        extractedPattern = IBoard::getPlayer2() &  (mask << convertedCoordinate);
    extractedPattern >>= convertedCoordinate;
    return patternBitset(extractedPattern.to_ulong());
}

patternBitset DiagBoard::extractPatternReversed(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const{
    int xEnd = xPos - length % getWidth();
    int yEnd = yPos - (length / getWidth());

    if (isValidPos(xEnd, yEnd) == false || (xEnd < yPos + 1 && xPos > yPos + 1))
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