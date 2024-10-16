#ifndef __TRANSPOSEDBOARD_HPP__
#define __TRANSPOSEDBOARD_HPP__

# include "IBoard.hpp"

class TransposedBoard: public IBoard{
    public:
        TransposedBoard();
        ~TransposedBoard();
        
        TransposedBoard(const TransposedBoard &cpy);
        TransposedBoard &operator=(const TransposedBoard &rhs);

        // bool operator==(const TransposedBoard &a);
        
        uint16_t     convertCoordinate(uint8_t x, uint8_t y) const noexcept;
        // patternBitset extractPattern(uint8_t xStart, uint8_t yStart, uint8_t length, int player) const;
        // patternBitset extractPatternReversed(uint8_t xPos, uint8_t yPos, uint8_t length, int player) const;

        // void    patternMatching();
};

#endif