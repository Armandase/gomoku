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

// IBoard::patternBitset AntiDiagBoard::extractPattern(uint16 xPos, uint16 yPos, uint16 length, int player) const{
//     int xEnd = xPos + length % this->_width;
//     int yEnd = yPos + (length / this->_width);

//     if (this->isPosValid(xEnd, yEnd) == false)
//         return nullptr;

//     // if (xPos <= yEnd + 1 && xEnd >= yEnd + 1)
//     //     handleDiag = false;
//     // if (this->_width - xPos <= yEnd - 1 && this->_width - xEnd >= yEnd - 1)
//     //     handleAntiDiag = false;
    
//     int convertedCoordinate = this->convertCoordinate(x, y);

//     patternBitset result(0);

//     bitboard mask(15);
//     bitboard extractedPattern(0);
//     if (player == this->_idPlayer1)
//         extractedPattern = this->_player1 &  (mask << convertedCoordinate);
//     else
//         extractedPattern = this->_player2 &  (mask << convertedCoordinate);
        
//     return patternBitset(pattern.to_ulong());
// }
