#include "../inc/algorithm.hpp"
#include "../inc/TranspositionTable.hpp"

bool times_up(const timePoint& start)
{
    const timePoint now = std::chrono::high_resolution_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() >= TIME_UP)
        return true;
    return false;
}

int alphaBetaWithMemory(t_playerGame& node, int alpha, int beta, int depth,
    TranspositionTable& memory)
{
    int heuristic = 0;
    const dataTranspositionTable_t* founded = memory.retrieve(node.game);
    if (founded != nullptr) {
        if (founded->lowerbound >= beta)
            return founded->lowerbound;
        else if (founded->upperbound <= alpha)
            return founded->upperbound;
        alpha = std::max(alpha, founded->lowerbound);
        beta = std::min(beta, founded->upperbound);
    }
    if (depth == 0)
        heuristic = node.game.globalHeurisitic(depth % 2);
    else if (depth % 2 == 0) { // maximization node
        heuristic = std::numeric_limits<int>::min();
        auto a = alpha;
        // BESOIN DE DEFINIR UN VRAI PLAYER
        gameSet possibleMoves = generatePossibleMoves(node.game, depth % 2);
        for (auto it = possibleMoves.begin(); it != possibleMoves.end() && heuristic < beta; ++it) {
            heuristic = std::max(heuristic, alphaBetaWithMemory(*it, a, beta, depth - 1, memory));
            a = std::max(a, heuristic);
        }
    } else { // minimization node
        heuristic = std::numeric_limits<int>::max();
        auto b = beta;
        gameSet possibleMoves = generatePossibleMoves(node.game, depth % 2);
        for (auto it = possibleMoves.begin(); it != possibleMoves.end() && heuristic > beta; ++it) {
            heuristic = std::min(heuristic, alphaBetaWithMemory(*it, alpha, b, depth - 1, memory));
            b = std::min(b, heuristic);
        }
    }
    if (heuristic <= alpha) {
        memory.store(node.game, heuristic, UPPERBOUND);
    }
    if (heuristic > alpha && heuristic < beta) {
        memory.store(node.game, heuristic, LOWERBOUND);
        memory.store(node.game, heuristic, UPPERBOUND);
    }
    if (heuristic >= beta) {
        memory.store(node.game, heuristic, LOWERBOUND);
    }
    return heuristic;
}

t_playerGame& mtdf(t_playerGame& root, int firstGuess, uint16_t depth, TranspositionTable& memory)
{
    int upperbound = std::numeric_limits<int>::max();
    int lowerbound = std::numeric_limits<int>::min();
    // int heuristic = firstGuess;
    int beta = 0;
    t_playerGame node = root;
    node.game.setHeuristic(0);

    while (lowerbound < upperbound) {
        beta = node.game.getHeuristic() + (node.game.getHeuristic() == lowerbound);

        auto res_alphahBetaMemroy = alphaBetaWithMemory(root, beta - 1, beta,
            depth, memory);
        std::cout << "res_alphahBetaMemroy: " << res_alphahBetaMemroy << std::endl;
        // node = alphaBetaWithMemory(root, beta - 1, beta, depth, memory);

        // if (node.getHeurisitic() < beta)
        //     upperbound = node.getHeurisitic();
        // else
        //     lowerbound = node.getHeurisitic();
    }
    return node;
}

t_playerGame iterativeDeepening(t_playerGame& root)
{
    TranspositionTable memory;
    int firstGuess = 0;
    const timePoint start = std::chrono::high_resolution_clock::now();

    t_playerGame node = root;
    for (int i = 1; i < DEPTH; i++) {
        node = mtdf(root, firstGuess, i, memory);
        if (times_up(start) == true)
            break;
        firstGuess = node.game.getHeuristic();
    }

    return node;
}