#ifndef __TRANSPOSEDBOARD_HPP__
#define __TRANSPOSEDBOARD_HPP__

#include "IBoard.hpp"

class TransposedBoard : public IBoard {
public:
    TransposedBoard();
    ~TransposedBoard();

    TransposedBoard(const TransposedBoard& cpy);
    TransposedBoard& operator=(const TransposedBoard& rhs);

    uint16_t convertCoordinate(uint16_t x, uint16_t y) const noexcept;
    patternBitset extractPattern(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const;
    patternBitset extractPatternReversed(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const;
};

#endif