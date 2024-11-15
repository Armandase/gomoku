#include "../inc/TranspositionTable.hpp"
#include "../inc/algorithm.hpp"

bool times_up(const timePoint& start)
{
    const timePoint now = std::chrono::high_resolution_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() >= TIME_UP)
        return true;
    return false;
}

t_playerGame alphaBetaWithMemory(t_playerGame& node, int alpha, int beta, int depth,
    TranspositionTable& memory)
{
    t_playerGame result = node;
    const dataTranspositionTable_t* founded = memory.retrieve(node.game);
    if (founded != nullptr) {
        if (founded->lowerbound >= beta) {
            node.game.setHeuristic(founded->lowerbound);
            return node;
        } else if (founded->upperbound <= alpha) {
            node.game.setHeuristic(founded->upperbound);
            return node;
        }
        alpha = std::max(alpha, founded->lowerbound);
        beta = std::min(beta, founded->upperbound);
    }
    if (depth == 0 || isTerminal(node.game, node.stone.player)) {
        result = node;
        result.game.setHeuristic(node.game.globalHeuristic(node.stone.player));
    } else if (node.stone.player == BLACK) { // maximization node
        result.game.setHeuristic(std::numeric_limits<int>::min());
        int64_t a = alpha;
        gameSet possibleMoves = generatePossibleMoves(node.game, node.stone.player);

        for (auto it = possibleMoves.begin(); it != possibleMoves.end() && result.game.getHeuristic() < beta; ++it) {
            it->stone.player = node.stone.player == BLACK ? WHITE : BLACK;
            t_playerGame ret = alphaBetaWithMemory(*it, a, beta, depth - 1, memory);
            if (ret.game.getHeuristic() > result.game.getHeuristic())
                result = ret;
            a = std::max(a, result.game.getHeuristic());
        }
    } else { // minimization node
        result.game.setHeuristic(std::numeric_limits<int>::max());
        int64_t b = beta;
        gameSet possibleMoves = generatePossibleMoves(node.game, node.stone.player);
        for (auto it = possibleMoves.begin(); it != possibleMoves.end() && result.game.getHeuristic() > alpha; ++it) {
            it->stone.player = node.stone.player == BLACK ? WHITE : BLACK;
            t_playerGame ret = alphaBetaWithMemory(*it, alpha, b, depth - 1, memory);
            if (ret.game.getHeuristic() < result.game.getHeuristic())
                result = ret;
            b = std::min(b, result.game.getHeuristic());
        }
    }
    if (result.game.getHeuristic() <= alpha) {
        memory.store(node.game, result.game.getHeuristic(), UPPERBOUND);
    }
    if (result.game.getHeuristic() > alpha && result.game.getHeuristic() < beta) {
        memory.store(node.game, result.game.getHeuristic(), LOWERBOUND);
        memory.store(node.game, result.game.getHeuristic(), UPPERBOUND);
    }
    if (result.game.getHeuristic() >= beta) {
        memory.store(node.game, result.game.getHeuristic(), LOWERBOUND);
    }
    return result;
}

t_playerGame mtdf(t_playerGame& root, uint16_t depth, TranspositionTable& memory, const timePoint& start, int player)
{
    int upperbound = std::numeric_limits<int>::max();
    int lowerbound = std::numeric_limits<int>::min();
    int beta = 0;
    t_playerGame node = root;

    while (lowerbound < upperbound) {
        beta = node.game.getHeuristic() + (node.game.getHeuristic() == lowerbound);
        node.stone.player = player;
        node = alphaBetaWithMemory(node, beta - 1, beta, depth, memory);
        if (node.game.getHeuristic() < beta)
            upperbound = node.game.getHeuristic();
        else
            lowerbound = node.game.getHeuristic();

        if (times_up(start) == true)
            break;
    }
    return node;
}

t_playerGame iterativeDeepening(Game& root, int player)
{
    TranspositionTable memory;
    const timePoint start = std::chrono::high_resolution_clock::now();
    int firstGuess = 0;

    t_playerGame node;
    node.game = root;
    node.game.setHeuristic(0);
    node.stone.player = player;

    for (int i = DEPTH; i >= 0; i--) {
        if ((i + 2) % 2 == (DEPTH + 2) % 2)
            node
                = mtdf(node, i, memory, start, player);
        else
            node = mtdf(node, i, memory, start, player == BLACK ? WHITE : BLACK);
        if (times_up(start) == true)
            break;
    }

    node.game.getClassicBoard().printBoard();
    return node;
}