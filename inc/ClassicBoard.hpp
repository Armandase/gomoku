#ifndef __CLASSICBOARD_HPP__
#define __CLASSICBOARD_HPP__

# include "IBoard.hpp"

class ClassicBoard: public IBoard{
    public:
        ClassicBoard();
        ~ClassicBoard();
        
        ClassicBoard(const ClassicBoard &cpy);
        ClassicBoard &operator=(const ClassicBoard &rhs);

        // bool operator==(const ClassicBoard &a);
        
        uint16_t     convertCoordinate(uint8_t x, uint8_t y) const noexcept;
        // patternBitset extractPattern(uint8_t xStart, uint8_t yStart, uint8_t length, int player) const;
        // patternBitset extractPatternReversed(uint8_t xPos, uint8_t yPos, uint8_t length, int player) const;

        // void    patternMatching();
};

#endif