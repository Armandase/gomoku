#ifndef HEURISTIC_HPP
# define HEURISTIC_HPP

#include "iostream"
#include "utils.hpp"

class Heuristic
{
	public:
        Heuristic(int player, const vector2d& game);
        ~Heuristic();

        int heuristic();
        const vector2d getGame() const;
    private:
        int     counterAnalysis(int count, bool capture, int empty, int inRow, int player);
        bool    checkCapture(int checkY, int checkX, int dirY, int dirX, int player);

        const vector2d _game;
        static constexpr int   dirX[8] = { 0, 0, 1, -1, 1, -1, 1, -1};
        static constexpr int   dirY[8] = { 1, -1, 0, 0, 1, -1, -1, 1};
        const int   _initPlayer;
        int         _heuristic;
        int         _index;
};

#endif