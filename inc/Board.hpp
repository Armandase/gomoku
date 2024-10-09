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
            ANTIDIAG
        } PatternType;
        typedef std::bitset<(BOARD_SIZE + 1) * (BOARD_SIZE + 1)> bitboard;
        typedef std::map<PatternType, patternBitset> patternMap;
        typedef std::pair<PatternType, patternBitset> patternPair;
    public:
        Board(void);
        ~Board();
        
        Board(const Board &cpy);
        Board &operator=(const Board &rhs);

        void    setPos(int x, int y, int player);
        bool     isValidPos(int x, int y);
        int    coordinateToTranspose1D(int x, int y) const;
        int    coordinateToDiag1D(int x, int y) const;
        int    coordinateToAntiDiag1D(int x, int y) const;
        void    removePos(int x, int y);
        int     getPos(int x, int y) const;
        patternMap extractPatterns(int xStart, int yStart, int length, int player) const;
        bool    isPosEmpty(int x, int y) const;

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
        int _idPlayer1;
        int _idPlayer2;
};

#endif