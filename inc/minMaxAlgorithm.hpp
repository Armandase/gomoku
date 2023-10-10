#ifndef __MINMAXALGORITHM_HPP__
# define __MINMAXALGORITHM_HPP__

# include "gomoku.hpp"
# include <algorithm>
# include <map>
# include "Heuristic.hpp"

void    minMaxAlgorithm(vector2d&, int&,  SDL_Renderer *);

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

typedef struct t_cost{
    int heuristic;
    int x;
    int y;
} cost;

// int heuristic(const vector2d &game, int player, const int y, const int x);
bool checkDoubleThree(vector2d& copy, int y, int x, int dirY, int dirX, int center);

#endif // !__MINMAXALGORITHM_HPP__