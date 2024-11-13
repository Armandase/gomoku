#ifndef __IBOARD_HPP__
#define __IBOARD_HPP__

#include <bitset>
#include <map>
#include <iostream>
#include <iomanip>

#include "gomoku.hpp"
# include "utils.hpp"

// bitboard representation of the board

class IBoard{
    public:
        typedef std::bitset<NB_PLACEMENTS> bitboard;

    public:
        IBoard();
        IBoard(bitboard& player1, bitboard& player2, uint16_t width, uint16_t idPlayer1, uint16_t idPlayer2);
        virtual ~IBoard() = 0;
        
        IBoard(const IBoard &cpy);
        IBoard &operator=(const IBoard &rhs);
        bool operator==(const IBoard &rhs);

        uint16_t getPos(uint16_t x,uint16_t y) const;
        uint16_t getWidth() const noexcept;
        uint16_t getIdPlayer1() const noexcept;
        uint16_t getIdPlayer2() const noexcept;
        bitboard getPlayer1() const noexcept;
        bitboard getPlayer2() const noexcept;
        virtual bool findMatch(uint16_t x, uint16_t y, uint16_t player, bitboard& mask, uint16_t length);
        
        bool    isValidPos(uint16_t x, uint16_t y) const;
        bool    isPosEmpty(uint16_t x, uint16_t y) const;
        void    setPos(uint16_t x, uint16_t y, int player);
        void    removePos(uint16_t x, uint16_t y);
        
        void    resetBoard();
        void    printBoard() const;

        virtual uint16_t  convertCoordinate(uint16_t x, uint16_t y) const = 0;

        virtual patternBitset extractPattern(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const = 0;
        virtual patternBitset extractPatternReversed(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const = 0;
        
    private:
        void printBoardX() const;
        void swapBits(bitboard& board, int pos1, int pos2);

        bitboard _player1;
        bitboard _player2;

        uint16_t _width;
        uint16_t _idPlayer1;
        uint16_t _idPlayer2;
};

#endif