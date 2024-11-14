#ifndef __ALGORITHM_HPP__
#define __ALGORITHM_HPP__

#include <chrono>

#include "../inc/Game.hpp"

typedef std::chrono::time_point<std::chrono::high_resolution_clock> timePoint;
// typedef std::vector<Game> gameSet;
typedef struct s_stone {
    int x;
    int y;
    int player;
} t_stone;

typedef struct s_playerGame {
    t_stone stone;
    Game game;
} t_playerGame;

typedef std::vector<t_playerGame> gameSet;

// Game iterativeDeepening(Game& root);
bool times_up(const timePoint& start);

int getCurrentPlayer(int depth, int initPlayer);
IBoard::bitboard getSurroundingBits(Game& game);

gameSet generatePossibleMoves(Game& game, int player);

t_playerGame findBestMove(Game& root, int depth, int player);

// struct CompareHeuristic {
//     bool operator()(const Heuristic& a, const Heuristic& b) const {
//         return a.getHeuristic() > b.getHeuristic();
//     }
// };

// typedef std::set<Heuristic, CompareHeuristic> heuristicSet;

#endif