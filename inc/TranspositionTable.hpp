#ifndef __TRANSPOSITION_TABLE_HPP__
#define __TRANSPOSITION_TABLE_HPP__

#define LOWERBOUND 0
#define UPPERBOUND 1

#include "Game.hpp"
#include "gomoku.hpp"
#include <unordered_map>

typedef struct s_dataTranspositionTable {
    int heuristic = 0;
    int lowerbound = std::numeric_limits<int>::min();
    int upperbound = std::numeric_limits<int>::max();
} dataTranspositionTable_t;

typedef std::unordered_map<size_t, dataTranspositionTable_t> transTable;

class TranspositionTable {
public:
    TranspositionTable();
    ~TranspositionTable();

    TranspositionTable(const TranspositionTable& cpy);
    TranspositionTable& operator=(const TranspositionTable& rhs);

    transTable getTable() const;

    void store(Game& game, int heuristic, int bound);
    const dataTranspositionTable_t* retrieve(Game& game) const;

private:
    transTable _table;
};

#endif