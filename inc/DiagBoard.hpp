#ifndef __DIAGBOARD_HPP__
#define __DIAGBOARD_HPP__

# include "IBoard.hpp"

class DiagBoard: public IBoard{
    public:
        DiagBoard();
        ~DiagBoard();
        
        DiagBoard(const DiagBoard &cpy);
        DiagBoard &operator=(const DiagBoard &rhs);

        // bool operator==(const DiagBoard &a);
        
        uint16_t     convertCoordinate(uint16_t x, uint16_t y) const noexcept;
        // patternBitset extractPattern(uint16_t xStart, uint16_t yStart, uint16_t length, int player) const;
        // patternBitset extractPatternReversed(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const;

        // void    patternMatching();

};

#endif