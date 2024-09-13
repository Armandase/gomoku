#ifndef __MINMAXALGORITHM_HPP__
# define __MINMAXALGORITHM_HPP__

# include "gomoku.hpp"
# include <algorithm>
# include <map>
# include "Heuristic.hpp"
# include "Board.hpp"


enum side {
    LEFT,
    RIGHT,
    TOP,
    TOP_RIGHT,
    TOP_LEFT,
    BOTTOM,
    BOTTOM_RIGHT,
    BOTTOM_LEFT,
};

enum comparison {
    MAX,
    MIN,
};

struct CompareHeuristic {
    bool operator()(const Heuristic& a, const Heuristic& b) const {
        return a.getHeuristic() < b.getHeuristic();
    }
};

typedef std::set<Heuristic, CompareHeuristic> heuristicSet;

void    minMaxAlgorithm(Board&, int&,  SDL_Renderer *);
bool checkDoubleThree(Board& copy, int y, int x, int dirY, int dirX, int center);

#endif // !__MINMAXALGORITHM_HPP__