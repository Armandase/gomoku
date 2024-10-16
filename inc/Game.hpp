#ifndef __GAME_HPP__
#define __GAME_HPP__

# include "ClassicBoard.hpp" 
# include "TransposedBoard.hpp" 
# include "AntiDiagBoard.hpp" 
# include "DiagBoard.hpp" 

// bitboard representation of the board

class Game{
    public:
        Game();
        ~Game();
        
        Game(const Game &cpy);
        Game &operator=(const Game &rhs);

        void    addCapture(int player);
        uint16_t getCapture(int player);
        void    setPosToBoards(uint16_t x, uint16_t y, int player);
        void    removePosToBoards(uint16_t x, uint16_t y);

        ClassicBoard getClassicBoard() const noexcept;
        TransposedBoard getTransposedBoard() const noexcept;
        AntiDiagBoard getAntiDiagBoard() const noexcept;
        DiagBoard getDiagBoard() const noexcept;
    private:
        ClassicBoard    _classicBoard;
        TransposedBoard _transposedBoard;
        AntiDiagBoard   _antiDiagBoard;
        DiagBoard       _diagBoard;

        uint16_t _player1Capture;
        uint16_t _player2Capture;
};

#endif