#include "../inc/algorithm.hpp"
#include "../inc/TranspositionTable.hpp"

bool times_up(const timePoint& start){
    const timePoint now = std::chrono::high_resolution_clock::now();
 
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() >= TIME_UP)
        return true;
    return false;
}

// int computeHeuristic(const Game& node) {
//     return 0;
// }

// int alphaBetaWithMemory(Game& node, int alpha, int beta, int depth, TranspositionTable& memory){
//     int heuristic = 0;
//     if (memory.retrieve(node) == true){
//         if (node.lowerbound >= beta)
//             return node.lowerbound;
//         else if (node.upperbound >= alpha)
//             return node.upperbound;
//         alpha = std::max(alpha, node.lowerbound);
//         beta = std::min(beta, node.uppernound);
//     }
//     if (depth == 0)
//         heuristic = computeHeuristic(node);
//     // maximization node
//     else if (node == MAXNODE){
//         heuristic = std::numeric_limits<int>::min();
//         auto a = alpha;
//         auto c = firstchild(node);
//         while (heuristic < beta && c != NOCHILD){
//             heuristic = std::max(heuristic , alphaBetaWithMemory(c, a, beta, depth - 1, memory));
//             a = std::max(a, heuristic);
//             c = nextBrother(c);
//         }
//     } else {
//         heuristic = std::numeric_limits<int>::max();
//         auto b = beta;
//         auto c = firstchild(node);
//         while (heuristic > alpha && c != NOCHILD){
//             heuristic = std::min(heuristic , alphaBetaWithMemory(c, alpha, b, depth - 1, memory));
//             b = std::min(b, heuristic);
//             c = nextBrother(c);
//         }
//     }
//     if (heuristic <= alpha){
//         node.upperbound = heuristic
//         memory.store(node.upperbound);
//     }
//     if (heuristic > alpha && heuristic < beta){
//         node.lowerbound = heuristic;
//         node.upperbound = heuristic;
//         memory.store(n.lowerbound);
//         memory.store(n.upperbound);
//     }
//     if (heuristic >= beta){
//         node.lowerbound = heuristic;
//         memory.store(node.lowerbound);
//     }
//     return heuristic; 
// }

// Game& mtdf(Game& root, int firstGuess, uint16_t depth, TranspositionTable& memory){
//     int upperbound = std::numeric_limits<int>::max();
//     int lowerbound = std::numeric_limits<int>::min();
//     int heuristic = firstGuess;
//     int beta = 0;
//     Game node = root;

//     while(lowerbound < upperbound){
//         beta = heuristic + (heuristic == lowerbound);
        
//         node = alphaBetaWithMemory(root, beta - 1, beta, depth, memory);

//         if (node.getHeurisitic() < beta)
//             upperbound = node.getHeurisitic();
//         else
//             lowerbound = node.getHeurisitic();
//     }
//     return node;
// }

// Game iterativeDeepening(Game& root){
//     TranspositionTable memory;
//     int firstGuess = 0;
//     const timePoint start = std::chrono::high_resolution_clock::now();
    
//     Game node = root;
//     for (int i = 1; i < DEPTH; i++){
//         node = mtdf(root, firstGuess, i, memory);
//         if (times_up(start) == true)
//             break ;
//         firstGuess = node.getHeuristic();
//     }
    
//     return node;
// }