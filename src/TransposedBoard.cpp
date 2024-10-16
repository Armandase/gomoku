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

uint16_t  TransposedBoard::convertCoordinate(uint16_t x, uint16_t y) const noexcept
{
    return (y + x * IBoard::getWidth());
};

