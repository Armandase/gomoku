# include "../inc/TranspositionTable.hpp"

TranspositionTable::TranspositionTable():
    _table()
{
    _table.clear();
}

TranspositionTable::~TranspositionTable()
{
}

TranspositionTable::TranspositionTable(const TranspositionTable &cpy):
    _table(cpy.getTable())
{
}

TranspositionTable &TranspositionTable::operator=(const TranspositionTable &rhs){
    if (this != &rhs)
        _table = rhs._table;
    return (*this);
}

transTable TranspositionTable::getTable() const{
    return (_table);
}

void TranspositionTable::store(Game& game, int heuristic){
    // _table.insert({game, heuristic});
    _table.insert({game.hashGame(), heuristic});
}

bool TranspositionTable::retrieve(Game& game) const{
    // if (_table.count(game) > 0)
    if (_table.find(game.hashGame()) == _table.end())
        return false;
    return true;
}