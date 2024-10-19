#ifndef __TRANSPOSITION_TABLE_HPP__
# define __TRANSPOSITION_TABLE_HPP__

# include "Game.hpp"
# include "gomoku.hpp"
# include <unordered_map>

typedef std::unordered_map<size_t, int> transTable;

class TranspositionTable{
    public:
        TranspositionTable();
        ~TranspositionTable();
        
        TranspositionTable(const TranspositionTable &cpy);
        TranspositionTable &operator=(const TranspositionTable &rhs);

        transTable getTable() const;

        void store(Game& game, int heuristic);
        bool retrieve(Game& game) const;

    private:
        transTable _table;
};

#endif