#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <iostream>
#include <bitset>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include "gomoku.hpp"
# include "utils.hpp"
#include <map>

// bitboard representation of the board

class Board{
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
        Board(void);
        ~Board();
        
        Board(const Board &cpy);
        Board &operator=(const Board &rhs);

        bool operator==(const Board &a);

        bool     isValidPos(unsigned int x, unsigned int y) const;
        void    setPos(unsigned int x, unsigned int y, int player);
        int    coordinateToTranspose1D(unsigned int x, unsigned  int y) const;
        int    coordinateToDiag1D(unsigned int x, unsigned int y) const;
        int    coordinateToAntiDiag1D(unsigned int x, unsigned int y) const;
        void    removePos(unsigned int x, unsigned int y);
        int     getPos(unsigned int x,unsigned int y) const;
        int     getWidth() const;
        patternMap extractPatterns(unsigned int xStart, unsigned int yStart, unsigned int length, int player) const;
        patternMap extractPatternsReversed(unsigned int xPos, unsigned int yPos, unsigned int length, int player) const;

        bool    isPosEmpty(unsigned int x, unsigned int y) const;

        void    printBoard() const;
        void    printDiagBoard() const;
        void    printAntiDiagBoard() const;
        void    printTransposedBoard() const;
        void    resetBoard();
        // void    patternMatching();

        void    generateTransposedBoard();
        void    generateDiagBoard();
        void    generateAntiDiagBoard();
        void    checkDiagPattern();
        void    checkAntiDiagPattern();
        
        int     countInDirection(int startRow, int startCol, int rowDelta, int colDelta, int player);
        bool    checkDoubleThree(int col, int row, int player);
        void    addCapture(int player);
        int     getCapture(int player);

    private:
        void printBoardX() const;
        void swapBits(bitboard& board, int pos1, int pos2);
        // void generateDiagBoard();
        // void generateAntiDiagBoard();
        bitboard _player1;
        bitboard _player2;

        bitboard _player1Transposed;
        bitboard _player2Transposed;

        bitboard _player1Diag;
        bitboard _player2Diag;

        bitboard _player1AntiDiag;
        bitboard _player2AntiDiag;

        int _width = {BOARD_SIZE + 1};
        int _player1Capture;
        int _player2Capture;
        int _idPlayer1;
        int _idPlayer2;
};

#endif