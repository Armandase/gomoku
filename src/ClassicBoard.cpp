#include "../inc/ClassicBoard.hpp"
#include "../inc/Pattern.hpp"

ClassicBoard::ClassicBoard():
    IBoard()
{
    resetBoard();
}

ClassicBoard::~ClassicBoard(){

};

ClassicBoard::ClassicBoard(const ClassicBoard &cpy):
    IBoard::IBoard(cpy)
{
}

ClassicBoard &ClassicBoard::operator=(const ClassicBoard &rhs)
{
    if (this != &rhs)
    {
	    IBoard::operator=(rhs);
    }
    return (*this);
}

uint16_t  ClassicBoard::convertCoordinate(uint16_t x, uint16_t y) const noexcept
{
    return (x + y * IBoard::getWidth());
};


patternBitset ClassicBoard::extractPattern(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const{
    int xEnd = xPos + length % getWidth();

    if (isValidPos(xEnd, yPos) == false){
        return patternBitset(0);
    }

    int convertedCoordinate = this->convertCoordinate(xPos, yPos);
    bitboard mask((1 << length) - 1);
    bitboard extractedPattern(0);
    if (player == getIdPlayer1())
        extractedPattern = getPlayer1() &  (mask << convertedCoordinate);
    else
        extractedPattern = getPlayer2() &  (mask << convertedCoordinate);
    extractedPattern >>= convertedCoordinate;
    return patternBitset(extractedPattern.to_ulong());
}

patternBitset ClassicBoard::extractPatternReversed(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const{
    int xEnd = xPos - length % getWidth();

    if (isValidPos(xEnd, yPos) == false)
        return patternBitset(0);

    int convertedCoordinate = this->convertCoordinate(xEnd, yPos);

    bitboard mask((1 << length) - 1);
    bitboard extractedPattern(0);
    if (player == getIdPlayer1())
        extractedPattern = getPlayer1() &  (mask << convertedCoordinate);
    else
        extractedPattern = getPlayer2() &  (mask << convertedCoordinate);
    extractedPattern >>= convertedCoordinate;
    return patternBitset(extractedPattern.to_ulong());
}