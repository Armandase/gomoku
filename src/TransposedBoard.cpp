#include "../inc/TransposedBoard.hpp"
#include "../inc/Pattern.hpp"

TransposedBoard::TransposedBoard():
    IBoard()
{
    resetBoard();
}

TransposedBoard::~TransposedBoard(){

};

TransposedBoard::TransposedBoard(const TransposedBoard &cpy):
    IBoard::IBoard(cpy)
{
}

TransposedBoard &TransposedBoard::operator=(const TransposedBoard &rhs)
{
    if (this != &rhs)
    {
	    IBoard::operator=(rhs);
    }
    return (*this);
}

// bool TransposedBoard::operator==(const TransposedBoard &a){
//     if (
//         this->_player1 == a._player1 &&
//         this->_player2 == a._player2
//     )
//         return true;
//     return false;
// }

uint16_t  TransposedBoard::convertCoordinate(uint16_t x, uint16_t y) const noexcept
{
    return (y + x * IBoard::getWidth());
};

// IBoard::patternBitset TransposedBoard::extractPattern(uint16 xPos, uint16 yPos, uint16 length, int player) const{
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
