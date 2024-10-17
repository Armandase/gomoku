#ifndef __GAME_HPP__
#define __GAME_HPP__

# include "ClassicBoard.hpp" 
# include "TransposedBoard.hpp" 
# include "AntiDiagBoard.hpp" 
# include "DiagBoard.hpp" 
# include "Pattern.hpp"

// bitboard representation of the board

class Game{
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
        typedef std::map<Game::PatternType, patternBitset> patternMap;
        typedef std::pair<Game::PatternType, patternBitset> patternPair;
    public:
        Game();
        ~Game();
        
        Game(const Game &cpy);
        Game &operator=(const Game &rhs);

        void    addCapture(int player);
        uint16_t getCapture(int player);
        void    setPosToBoards(uint16_t x, uint16_t y, int player);
        void    removePosToBoards(uint16_t x, uint16_t y);

        ClassicBoard& getClassicBoard() noexcept;
        TransposedBoard& getTransposedBoard() noexcept;
        AntiDiagBoard& getAntiDiagBoard() noexcept;
        DiagBoard& getDiagBoard() noexcept;

        patternMap extractPatterns(uint16_t x, uint16_t y, uint16_t length, uint16_t player);
        bool checkDoubleThree(uint16_t x, uint16_t y, uint16_t player);
    private:
        ClassicBoard    _classicBoard;
        TransposedBoard _transposedBoard;
        AntiDiagBoard   _antiDiagBoard;
        DiagBoard       _diagBoard;

        uint16_t _player1Capture;
        uint16_t _player2Capture;
};

#endif