

// function MTDF(root : node_type; f : integer; d : integer) : integer;

//     g := f;
//     upperbound := +INFINITY;
//     lowerbound := -INFINITY;
//     repeat
//         if g == lowerbound then beta := g + 1 else beta := g;
//         g := AlphaBetaWithMemory(root, beta - 1, beta, d);
//         if g < beta then upperbound := g else lowerbound := g;
//     until lowerbound >= upperbound;
//     return g;

int mtdf(Game& game, int initialEvaluation, uint16_t depth){
    auto g = initialEvaluation;
    int upperbound = std::numeric_limits<int>::max();
    int lowerbound = std::numeric_limits<int>::min();
}