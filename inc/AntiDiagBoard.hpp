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
        
        uint16_t     convertCoordinate(uint8_t x, uint8_t y) const noexcept;
        // patternBitset extractPattern(uint8_t xStart, uint8_t yStart, uint8_t length, int player) const;
        // patternBitset extractPatternReversed(uint8_t xPos, uint8_t yPos, uint8_t length, int player) const;

        // void    patternMatching();
};

#endif