#ifndef __HEURISTIC_HPP__
#define __HEURISTIC_HPP__

#include "iostream"
#include "utils.hpp"
#include "Board.hpp"
#include <memory>

class Heuristic
{
	public:
        Heuristic(int player, const Board& game, int x, int y);
        ~Heuristic();
        Heuristic(const Heuristic &cpy);
        Heuristic &operator=(const Heuristic &rhs);

        int globalHeuristic();
        int localHeuristic(int x, int y);
        const Board& getGame() const;
        int getHeuristic() const { return (this->_heuristic); }
        int getX() const { return (this->_xPos); }
        int getY() const { return (this->_yPos); }
        void setHeuristic(int heuristic) { this->_heuristic = heuristic; }
    private:
        int     counterAnalysis(int count, bool capture, int empty, int inRow, int player);
        bool    checkCapture(int checkY, int checkX, int dirY, int dirX, int player);

        static constexpr int   dirX[8] = { 0, 0, 1, -1, 1, -1, 1, -1};
        static constexpr int   dirY[8] = { 1, -1, 0, 0, 1, -1, -1, 1};
        //a shared pointer to the game
        std::shared_ptr<Board> _gamePtr;

        int   _initPlayer;
        int         _heuristic;
        int         _xPos;
        int         _yPos;
};

#endif