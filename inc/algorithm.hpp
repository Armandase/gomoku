#ifndef __ALGORITHM_HPP__
# define __ALGORITHM_HPP__

# include <chrono>
# include "../inc/Game.hpp"

typedef std::chrono::time_point<std::chrono::high_resolution_clock> timePoint;

// Game iterativeDeepening(Game& root);
bool times_up(const timePoint& start);

# endif