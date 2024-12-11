#ifndef __ALGORITHM_HPP__
#define __ALGORITHM_HPP__

#include <chrono>

#include "../inc/Game.hpp"

typedef std::chrono::time_point<std::chrono::high_resolution_clock> timePoint;
// typedef std::vector<Game> gameSet;
typedef struct s_stone {
    int x = 0;
    int y = 0;
    int player = 0;
} t_stone;

typedef struct s_playerGame {
    t_stone stone;
    Game game;
    int depth = 0;
} t_playerGame;

typedef std::vector<t_playerGame> gameSet;

t_playerGame iterativeDeepening(Game& root, int player);
bool times_up(const timePoint& start);
bool isTerminal(Game& node, int player);

IBoard::bitboard getSurroundingBits(Game& game);

gameSet generatePossibleMoves(Game& game, int player, bool max, int depth);

t_playerGame findBestMove(Game& root, int depth, int player);
t_playerGame findBestMovePVS(Game& root, int depth, int player);
t_playerGame findBestMovePVSmultithread(Game& root, int depth, int player);

#endif