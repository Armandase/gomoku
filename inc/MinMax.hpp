#ifndef MINMAX_HPP
# define MINMAX_HPP

# include "gomoku.hpp"
# include "Heuristic.hpp"

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


class MinMax
{
private:
    int _initPlayer;
    int _captureCounter[2];
    int _depth;
    SDL_Renderer *_renderer;
    
public:
    MinMax(int depth, SDL_Renderer* renderer);
    ~MinMax();

    cost    minMaxRecursive(const vector2d &board, int player, int depth, const int y, const int x, int alpha, int beta);
    cost    finCorrectValue(const std::vector<cost>& recursiveResult, int minOrMax);
    int     checkWin(const vector2d& game, const int y, const int x, const int player);
    bool    emptyNeighbour(const vector2d &game, const int x, const int y);
    void    minMaxAlgorithm(vector2d &board, int player, int captureCounter[2]);
};

int     heuristic(const vector2d &game, int player, int captures[2]);
bool    openSideFour(const vector2d &board, int player);
bool    openSideThree(const vector2d &board, int player);
bool    openSideTwo(const vector2d &board, int player);

#endif