#ifndef __MINMAXALGORITHM_HPP__
#define __MINMAXALGORITHM_HPP__

# include <algorithm>
# include <map>
# include <tuple>
# include <future>

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
int     indexOfMaxValue(const std::vector<Heuristic>& vec);
int     getCurrentPlayer(int depth, int initPlayer);
bool    emptyNeighbour(const Board &game, const int x, const int y);
bool    checkWin(const Heuristic& heuristic);
bool    validGame(Board& copy, int yPoint, int xPoint, int player);
heuristicSet generatePossibleMoves(Board& game, int player);


#endif