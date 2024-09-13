#ifndef __MINMAXALGORITHM_HPP__
# define __MINMAXALGORITHM_HPP__

# include "gomoku.hpp"
# include <algorithm>
# include <map>
# include "Heuristic.hpp"
# include "Board.hpp"

void    minMaxAlgorithm(Board&, int&,  SDL_Renderer *);

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

typedef struct t_data{
    const Board game;
    int init_player;
    int player; 
    int depth; 
    int yGame; 
    int xGame; 
    int alpha; 
    int beta;
    cost finalRes;
} data;

// int heuristic(const vector2d &game, int player, const int y, const int x);
bool checkDoubleThree(Board& copy, int y, int x, int dirY, int dirX, int center);

#endif // !__MINMAXALGORITHM_HPP__