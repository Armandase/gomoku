#ifndef HEURISTIC_HPP
# define HEURISTIC_HPP

#include "iostream"
#include "utils.hpp"
#include "Board.hpp"
#include <memory>

class Heuristic
{
	public:
        Heuristic(int player, const Board& game, int x, int y);
        ~Heuristic();

        int heuristic();
        const Board& getGame() const;
        int getHeuristic() const { return (this->_heuristic); }
        int getIndex() const { return (this->_index); }
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

        const int   _initPlayer;
        int         _heuristic;
        int         _index;
        int         _xPos;
        int         _yPos;
};

#endif