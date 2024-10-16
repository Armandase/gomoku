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