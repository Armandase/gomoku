#include "../inc/algorithm.hpp"
#include <future>

/*
function pvs(node, depth, α, β, color) is
    if depth = 0 or node is a terminal node then
        return color × the heuristic value of node
    for each child of node do
        if child is first child then
            score := −pvs(child, depth − 1, −β, −α, −color)
        else
            score := −pvs(child, depth − 1, −α − 1, −α, −color) (* search with a null window *)
            if α < score < β then
                score := −pvs(child, depth − 1, −β, −α, −color) (* if it failed high, do a full re-search *)
        α := max(α, score)
        if α ≥ β then
            break (* beta cut-off *)
    return α
*/

int pvs(t_playerGame& node, int alpha, int beta, int depth, int maxNode, const timePoint& start)
{
    if (depth <= 0 || isTerminal(node.game, node.stone.player) || times_up(start)) {
        if (maxNode)
            return node.game.heuristicLocal(node.stone.x, node.stone.y, node.stone.player);
        else
            return -node.game.heuristicLocal(node.stone.x, node.stone.y, node.stone.player);
    }
    int nextPlayer = node.stone.player == WHITE ? BLACK : WHITE;
    gameSet possibleMoves = generatePossibleMoves(node.game, nextPlayer, !maxNode, depth);

    int score = 0;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); ++it) {
        if (it == possibleMoves.begin())
            score = -pvs(*it, -beta, -alpha, depth - 1, !maxNode, start);
        else {
            score = -pvs(*it, -alpha - 1, -alpha, depth - 1, !maxNode, start);
            if (alpha < score && score < beta)
                score = -pvs(*it, -beta, -alpha, depth - 1, !maxNode, start);
        }
        if (score == INT_MAX || score == INT_MIN) {
            return score;
        }
        alpha = std::max(alpha, score);
        if (alpha >= beta)
            break;
    }
    return alpha;
}

t_playerGame findBestMovePVS(Game& root, int depth, int player)
{
    gameSet possibleMoves = generatePossibleMoves(root, player, true, depth);
    if (possibleMoves.empty()) {
        t_playerGame playerGame;
        playerGame.game = root;
        playerGame.stone.player = player;
        return playerGame;
    }

    t_playerGame bestMove = possibleMoves.front();
    --depth;
    int bestValue = std::numeric_limits<int>::min();
    int result = std::numeric_limits<int>::min();
    int highestDepth = -1;
    timePoint start = std::chrono::high_resolution_clock::now();
    for (auto& move : possibleMoves) {
        result = pvs(move,
            std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), depth, true, start);
        if (result > bestValue) {
            bestValue = result;
            bestMove = move;
            highestDepth = move.depth;
        } else if (result == bestValue && move.depth > highestDepth) {
            bestMove = move;
            bestValue = result;
            highestDepth = move.depth;
        }
        if (times_up(start))
            break;
    }
    return bestMove;
}

t_playerGame findBestMovePVSmultithread(Game& root, int depth, int player)
{
    gameSet possibleMoves = generatePossibleMoves(root, player, true, depth);
    if (possibleMoves.empty()) {
        t_playerGame playerGame;
        playerGame.game = root;
        playerGame.stone.player = player;
        return playerGame;
    }

    std::vector<std::future<int>> threadResult;
    t_playerGame bestMove = possibleMoves.front();

    --depth;
    timePoint start = std::chrono::high_resolution_clock::now();
    for (auto& move : possibleMoves) {
        threadResult.push_back(std::async(std::launch::async, pvs, std::ref(move),
            std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), depth, true, start));
    }
    int bestValue = std::numeric_limits<int>::min();
    int result = std::numeric_limits<int>::min();
    int highestDepth = -1;
    for (size_t i = 0; i < threadResult.size(); ++i) {
        result = threadResult[i].get();
        if (result > bestValue) {
            bestValue = result;
            bestMove = possibleMoves[i];
            highestDepth = possibleMoves[i].depth;
        } else if (result && result == bestValue && possibleMoves[i].depth > highestDepth) {
            highestDepth = possibleMoves[i].depth;
            bestMove = possibleMoves[i];
            bestValue = result;
        }
        if (times_up(start))
            break;
    }

    return bestMove;
}
