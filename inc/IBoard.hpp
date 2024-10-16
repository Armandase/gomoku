#ifndef __IBOARD_HPP__
#define __IBOARD_HPP__

#include <bitset>
#include <map>

#include "gomoku.hpp"
# include "utils.hpp"

// bitboard representation of the board

class IBoard{
    public:
        typedef enum {
            DEFAULT,
            TRANSPOS,
            DIAG,
            ANTIDIAG,
            REV_DEFAULT,
            REV_TRANSPOS,
            REV_DIAG,
            REV_ANTIDIAG,
        } PatternType;
        typedef std::bitset<(BOARD_SIZE + 1) * (BOARD_SIZE + 1)> bitboard;
        typedef std::map<PatternType, patternBitset> patternMap;
        typedef std::pair<PatternType, patternBitset> patternPair;
    public:
        IBoard();
        IBoard(bitboard& player1, bitboard& player2, uint16_t width, uint16_t idPlayer1, uint16_t idPlayer2);
        virtual ~IBoard() = 0;
        
        IBoard(const IBoard &cpy);
        IBoard &operator=(const IBoard &rhs);

        uint16_t getPos(uint16_t x,uint16_t y) const;
        uint16_t getWidth() const noexcept;
        uint16_t getIdPlayer1() const noexcept;
        uint16_t getIdPlayer2() const noexcept;
        bitboard getPlayer1() const noexcept;
        bitboard getPlayer2() const noexcept;
        
        bool    isValidPos(uint16_t x, uint16_t y) const;
        bool    isPosEmpty(uint16_t x, uint16_t y) const;
        void    setPos(uint16_t x, uint16_t y, int player);
        void    removePos(uint16_t x, uint16_t y);
        
        void    resetBoard();
        void    printBoard() const;

        virtual uint16_t  convertCoordinate(uint16_t x, uint16_t y) const = 0;
        virtual patternBitset extractPattern(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const = 0;
        // virtual patternBitset extractPatternReversed(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const = 0;
        // void    convertBoard(const BoardClassic& board);
        
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