#ifndef __HEURISTIC_HPP__
#define __HEURISTIC_HPP__

#include "iostream"
#include "utils.hpp"
#include "Board.hpp"
#include <memory>

class Heuristic
{
	public:
        Heuristic(const Board& game, int x, int y, int xBegin, int yBegin);
        ~Heuristic();
        Heuristic(const Heuristic &cpy);
        Heuristic &operator=(const Heuristic &rhs);

        int globalHeuristic();
        int localHeuristic(int x, int y);
        const Board& getGame() const;
        int getHeuristic() const { return (this->_heuristic); }
        int getX() const { return (this->_xPos); }
        int getY() const { return (this->_yPos); }
        int getPlayer() const { return (_game.getPos(this->_xPos, this->_yPos)); }
        int getBeginX() const{ return (this->_xBeginPos); }
        int getBeginY() const{ return (this->_yBeginPos); }
        void setCoordinate(int x, int y) { this->_xPos = x; this->_yPos = y;}
        void setBeginCoordinate(int x, int y) { this->_xBeginPos = x; this->_yBeginPos = y;}
        void setHeuristic(int heuristic) { this->_heuristic = heuristic; }
    private:
        Heuristic();
        int     counterAnalysis(int count, bool capture, int empty, int inRow, int player);
        bool    checkCapture(int checkY, int checkX, int dirY, int dirX, int player);

        static constexpr int   dirX[8] = { 0, 0, 1, -1, 1, -1, 1, -1};
        static constexpr int   dirY[8] = { 1, -1, 0, 0, 1, -1, -1, 1};

        Board _game;

        int         _heuristic;
        int         _xPos;
        int         _yPos;
        int         _xBeginPos;
        int         _yBeginPos;
};

#endif