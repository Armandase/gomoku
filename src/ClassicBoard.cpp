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
    int xEnd = xPos + length % IBoard::getWidth();
    int yEnd = yPos + (length / IBoard::getWidth());

    if (IBoard::isValidPos(xEnd, yEnd) == false)
        return patternBitset(0);
    
    // if (xPos <= yEnd + 1 && xEnd >= yEnd + 1)
    //     handleDiag = false;
    // if (this->_width - xPos <= yEnd - 1 && this->_width - xEnd >= yEnd - 1)
    //     handleAntiDiag = false;
    
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
