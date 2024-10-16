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
        
        uint16_t     convertCoordinate(uint8_t x, uint8_t y) const noexcept;
        // patternBitset extractPattern(uint8_t xStart, uint8_t yStart, uint8_t length, int player) const;
        // patternBitset extractPatternReversed(uint8_t xPos, uint8_t yPos, uint8_t length, int player) const;

        // void    patternMatching();

};

#endif