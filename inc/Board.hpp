#ifndef __BOARD_HPP__
# define __BOARD_HPP__

# include <iostream>
# include <bitset>
# include <algorithm>
# include "gomoku.hpp"

// bitboard representation of the board

class Board{
    public:
        typedef std::bitset<(BOARD_SIZE + 1) * (BOARD_SIZE + 1)> bitboard;
    public:
        Board(void);
        ~Board();
        
        Board(const Board &cpy);
        Board &operator=(const Board &rhs);

        void    setPos(int x, int y, int player);
        void    removePos(int x, int y);
        int     getPos(int x, int y) const;
        bool    isPosEmpty(int x, int y) const;

        void    printBoard() const;
        void    printTransposedBoard() const;
        void    resetBoard();
        // void    patternMatching()

    private:
        void generateTransposedBoard();
        void swapBits(bitboard& board, int pos1, int pos2);
        // void generateDiagBoard();
        // void generateAntiDiagBoard();
        
        bitboard _player1;
        bitboard _player1Transposed;
        bitboard _player1Diag;
        bitboard _player1AntiDiag;

        bitboard _player2;
        bitboard _player2Transposed;
        bitboard _player2Diag;
        bitboard _player2AntiDiag;

        int _width = {BOARD_SIZE + 1};
        int _idPlayer1;
        int _idPlayer2;
};


#endif