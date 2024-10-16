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
        IBoard(bitboard& player1, bitboard& player2, uint8_t width, uint8_t idPlayer1, uint8_t idPlayer2);
        virtual ~IBoard() = 0;
        
        IBoard(const IBoard &cpy);
        IBoard &operator=(const IBoard &rhs);

        bool    isValidPos(uint8_t x, uint8_t y) const;
        void    setPos(uint8_t x, uint8_t y, int player);
        virtual uint16_t  convertCoordinate(uint8_t x, uint8_t y) const = 0;
        void    removePos(uint8_t x, uint8_t y);
        uint8_t getPos(uint8_t x,uint8_t y) const;
        uint8_t getWidth() const noexcept;
        uint8_t getIdPlayer1() const noexcept;
        uint8_t getIdPlayer2() const noexcept;

        bool    isPosEmpty(uint8_t x, uint8_t y) const;

        void    resetBoard();

        void    printBoard() const;

        // void    convertBoard(const BoardClassic& board);
        
        // patternBitset extractPatternReversed(uint8_t xPos, uint8_t yPos, uint8_t length, int player) const = 0;
        // patternBitset extractPattern(uint8_t xStart, uint8_t yStart, uint8_t length, int player) const = 0;

    private:
        void printBoardX() const;
        void swapBits(bitboard& board, int pos1, int pos2);

        bitboard _player1;
        bitboard _player2;

        uint8_t _width;
        uint8_t _idPlayer1;
        uint8_t _idPlayer2;
};

#endif