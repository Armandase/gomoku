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
        
        uint16_t     convertCoordinate(uint16_t x, uint16_t y) const noexcept;

        patternBitset extractPattern(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const;

        // patternBitset extractPattern(uint16_t xStart, uint16_t yStart, uint16_t length, int player) const;
        // patternBitset extractPatternReversed(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const;

        // void    patternMatching();
};

#endif