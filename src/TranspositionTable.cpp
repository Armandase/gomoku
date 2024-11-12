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

void TranspositionTable::store(Game& game, int heuristic, int bound){
    auto fouded = _table.find(game.hashGame());
    if (fouded != _table.end()){
        if (bound == LOWERBOUND)
            fouded->second.lowerbound = std::max(fouded->second.lowerbound, heuristic);
        else if (bound == UPPERBOUND)
            fouded->second.upperbound = std::min(fouded->second.upperbound, heuristic);
        fouded->second.heuristic = heuristic;
    } else {
        dataTranspositionTable_t data;
        data.heuristic = heuristic;
        _table.insert({game.hashGame(), data});
    }
}

const dataTranspositionTable_t* TranspositionTable::retrieve(Game& game) const{
    auto it = _table.find(game.hashGame());
    if (it == _table.end())
        return nullptr;
    return &it->second;
}