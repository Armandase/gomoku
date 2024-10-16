#ifndef __ANTIDIAGBOARD_HPP__
#define __ANTIDIAGBOARD_HPP__

# include "IBoard.hpp"

class AntiDiagBoard: public IBoard{
    public:
        AntiDiagBoard();
        ~AntiDiagBoard();
        
        AntiDiagBoard(const AntiDiagBoard &cpy);
        AntiDiagBoard &operator=(const AntiDiagBoard &rhs);

        // bool operator==(const AntiDiagBoard &a);
        
        uint16_t     convertCoordinate(uint16_t x, uint16_t y) const noexcept;
        // patternBitset extractPattern(uint16_t xStart, uint16_t yStart, uint16_t length, int player) const;
        // patternBitset extractPatternReversed(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const;

        // void    patternMatching();
};

#endif