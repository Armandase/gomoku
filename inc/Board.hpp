#ifndef __BOARD_HPP__
# define __BOARD_HPP__

# include <iostream>
# include <bitset>

# include "gomoku.hpp"

// bitboard representation of the board
class Board{
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
        void    resetBoard();
        // bool    checkWin(int x, int y);

    private:
        void generateTransposedBoard();
        void generateDiagBoard();
        void generateAntiDiagBoard();
        
        std::bitset<(BOARD_SIZE + 1) * (BOARD_SIZE + 1)> _player1;
        std::bitset<(BOARD_SIZE + 1) * (BOARD_SIZE + 1)> _player1Transposed;
        std::bitset<(BOARD_SIZE + 1) * (BOARD_SIZE + 1)> _player1Diag;
        std::bitset<(BOARD_SIZE + 1) * (BOARD_SIZE + 1)> _player1AntiDiag;

        std::bitset<(BOARD_SIZE + 1) * (BOARD_SIZE + 1)> _player2;
        std::bitset<(BOARD_SIZE + 1) * (BOARD_SIZE + 1)> _player2Transposed;
        std::bitset<(BOARD_SIZE + 1) * (BOARD_SIZE + 1)> _player2Diag;
        std::bitset<(BOARD_SIZE + 1) * (BOARD_SIZE + 1)> _player2AntiDiag;

        int _width = {BOARD_SIZE + 1};
        int _idPlayer1;
        int _idPlayer2;
};


#endif