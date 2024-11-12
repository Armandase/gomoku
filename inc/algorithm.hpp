#ifndef __ALGORITHM_HPP__
# define __ALGORITHM_HPP__

# include <chrono>
# include "../inc/Game.hpp"

typedef std::chrono::time_point<std::chrono::high_resolution_clock> timePoint;
typedef std::vector<Game> gameSet;

// Game iterativeDeepening(Game& root);
bool times_up(const timePoint& start);

int getCurrentPlayer(int depth, int initPlayer);
IBoard::bitboard getSurroundingBits(Game& game);

gameSet generatePossibleMoves(Game& game, int player);

// struct CompareHeuristic {
//     bool operator()(const Heuristic& a, const Heuristic& b) const {
//         return a.getHeuristic() > b.getHeuristic();
//     }
// };

// typedef std::set<Heuristic, CompareHeuristic> heuristicSet;



# endif