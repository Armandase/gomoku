#include <chrono>
#include <unordered_map>
#include "../inc/Game.hpp"

// Table de transposition pour stocker les valeurs des noeuds

// similare to heuristic :)
int evaluate(const Game& node) {
    return 0;
}

// Fonction pour récupérer une valeur dans la table de transposition
bool retrieve(const Game& node, int& lower_bound, int& upper_bound) {
    // Simuler une recherche dans une table de transposition
    return false; // Renvoie false si pas de valeur
}

// Fonction pour stocker un noeud dans la table de transposition
void store(const Game& node, int lower_bound, int upper_bound) {
    // Stocker les limites dans la table de transposition
}


int alphaBetaWithMemory(Game& node, int alpha, int beta, int depth, std::unordered_map<int, int>& transposition_table){
    int heuristic = 0;
    if retrieve(node) == true{
        if (node.lowerbound >= beta)
            return node.lowerbound;
        else if (node.upperbound >= alpha)
            return node.upperbound;
        alpha = std::max(aplha, node.lowerbound);
        beta = std::min(beta, node.uppernound);
    }
    if (depth == 0)
        heuristic = evaluate(node);
    // maximization node
    else if (node == MAXNODE){
        heuristic = std::numeric_limits<int>::min();
        auto a = alpha;
        auto c = firstchild(node);
        while (heuristic < beta && c != NOCHILD){
            heuristic = std::max(heuristic , alphaBetaWithMemory(c, a, beta, depth - 1, transposition_table));
            a = std::max(a, heuristic);
            c = nextBrother(c);
        }
    } else {
        heuristic = std::numeric_limits<int>::max();
        auto b = beta;
        auto c = firstchild(node);
        while (heuristic > alpha && c != NOCHILD){
            heuristic = std::min(heuristic , alphaBetaWithMemory(c, alpha, b, depth - 1, transposition_table));
            b = std::min(b, heuristic);
            c = nextBrother(c);
        }
    }
    if (heuristic <= alpha){
        node.upperbound = heuristic
        store(node.upperbound);
    }
    if (heuristic > alpha && heuristic < beta){
        node.lowerbound = heuristic;
        node.upperbound = heuristic;
        store(n.lowerbound);
        store(n.upperbound);
    }
    if (heuristic >= beta){
        node.lowerbound = heuristic;
        store(node.lowerbound);
    }
    return heuristic; 
}


Game& mtdf(Game& root, int firstGuess, uint16_t depth, std::unordered_map<int, int>& transposition_table){
    int upperbound = std::numeric_limits<int>::max();
    int lowerbound = std::numeric_limits<int>::min();
    int heuristic = firstGuess;
    int beta = 0;
    Game node = root;

    while(lowerbound < upperbound){
        beta = heuristic + (heuristic == lowerbound);
        
        node = alphaBetaWithMemory(root, beta - 1, beta, depth, transposition_table);

        if (node.getHeurisitic() < beta)
            upperbound = node.getHeurisitic();
        else
            lowerbound = node.getHeurisitic();
    }
    return node;
}

bool times_up(const std::chrono::time_point<std::chrono::high_resolution_clock>& start){
    const std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
 
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() >= 500 )
        return true;
    return false;
}

Game iterativeDeepening(Game& root){
    std::unordered_map<int, int> transposition_table;
    int firstGuess = 0;
    const std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    
    Game node = root;
    for (int i = 1; i < DEPTH; i++){
        node = mtdf(root, firstGuess, i, transposition_table);
        if (times_up(start) == true)
            break ;
        firstGuess = node.getHeuristic();
    }
    
    return node;
}

void test(){
    Game testGame();
    Game result = iterativeDeepening(game);
}
