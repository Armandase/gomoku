#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "AntiDiagBoard.hpp"
#include "ClassicBoard.hpp"
#include "DiagBoard.hpp"
#include "TransposedBoard.hpp"
// bitboard representation of the board

class Game {
public:
    typedef enum {
        CLASSIC,
        TRANSPOS,
        DIAG,
        ANTIDIAG,
        REV_CLASSIC,
        REV_TRANSPOS,
        REV_DIAG,
        REV_ANTIDIAG
    } PatternType;
    typedef std::map<Game::PatternType, patternBitset> patternMap;
    typedef std::pair<Game::PatternType, patternBitset> patternPair;

public:
    Game();
    ~Game();

    Game(const Game& cpy);
    Game& operator=(const Game& rhs);
    bool operator==(Game& rhs);

    void addCapture(int player);
    uint16_t getCapture(int player);
    void setPosToBoards(uint16_t x, uint16_t y, int player);
    void removePosToBoards(uint16_t x, uint16_t y);
    void resetBoards();
    bool isFull() const;
    bool isEmpty() const;

    ClassicBoard& getClassicBoard() noexcept;
    TransposedBoard& getTransposedBoard() noexcept;
    AntiDiagBoard& getAntiDiagBoard() noexcept;
    DiagBoard& getDiagBoard() noexcept;

    patternMap extractPatterns(uint16_t x, uint16_t y, uint16_t length, uint16_t player);

    void setHeuristic(int64_t heuristic);
    int64_t getHeuristic() const;

    bool isDoubleThree(uint16_t x, uint16_t y, uint16_t player);
    bool canCapture(uint16_t x, uint16_t y, uint16_t player);
    bool canBeCaptured(uint16_t x, uint16_t y, PatternType boardType, uint16_t player);
    std::vector<uint16_t> isCapture(uint16_t x, uint16_t y, uint16_t player);
    void handleCapture(uint16_t x, uint16_t y, std::vector<uint16_t>& capturesBoard, uint16_t player, Render& render);
    bool inFiveAtPos(uint16_t x, uint16_t y, uint16_t player);
    bool playerWin(uint16_t player);
    int heuristicLocal(int x, int y, int player);
    int globalHeuristic(int player);

private:
    ClassicBoard _classicBoard;
    TransposedBoard _transposedBoard;
    AntiDiagBoard _antiDiagBoard;
    DiagBoard _diagBoard;

    uint16_t _player1Capture;
    uint16_t _player2Capture;

    int64_t _heuristic;
};

#endif