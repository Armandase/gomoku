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
    int xEnd = xPos + length;

    // if (IBoard::isValidPos(xEnd, yPos) == false || (xPos <= yPos + 1 && xEnd >= yPos + 1)){
    std::cout << "xEnd" << xEnd << "Ypos" << yPos << std::endl;
    if (IBoard::isValidPos(xEnd, yPos) == false){
        return patternBitset(0);
    }
    
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

patternBitset DiagBoard::extractPatternReversed(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const{
    int xEnd = xPos - (length % getWidth()) + 1;

    // if (isValidPos(xEnd, yPos) == false || (xEnd < yPos + 1 && xPos > yPos + 1))
    if (isValidPos(xEnd, yPos) == false)
        return patternBitset(0);

    // int convertedCoordinate = this->convertCoordinate(xEnd + 1, yPos);
    int convertedCoordinate = xEnd + yPos * IBoard::getWidth();

    bitboard mask((1 << length) - 1);
    bitboard extractedPattern(0);
    if (player == getIdPlayer1())
        extractedPattern = getPlayer1() &  (mask << convertedCoordinate);
    else
        extractedPattern = getPlayer2() &  (mask << convertedCoordinate);
    extractedPattern >>= convertedCoordinate;
    return patternBitset(extractedPattern.to_ulong());
}