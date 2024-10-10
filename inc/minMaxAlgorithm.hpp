#ifndef __MINMAXALGORITHM_HPP__
#define __MINMAXALGORITHM_HPP__

# include <algorithm>
# include <map>

# include "gomoku.hpp"
# include "Heuristic.hpp"
# include "Board.hpp"
# include "Render.hpp"


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

void    minMaxAlgorithm(Board&, int&,  Render& render);
// bool checkDoubleThree(Board& copy, int y, int x, int dirY, int dirX, int center);

#endif