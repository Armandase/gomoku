#include "../inc/algorithm.hpp"
#include <future>

t_playerGame miniMax(t_playerGame& node, int depth, bool maximizingPlayer, int player)
{
    // if depth is 0(terminal node) or node is a terminal node(win or the board is full)
    if (depth <= 0 || isTerminal(node.game, player)) {
        if ((DEPTH + 2) % 2 == WHITE) {
            node.game.setHeuristic(node.game.globalHeuristic(player == WHITE ? BLACK : WHITE));
        } else {
            node.game.setHeuristic(node.game.globalHeuristic(player));
        }
        return node;
    }
    gameSet possibleMoves = generatePossibleMoves(node.game, player, maximizingPlayer, depth);
    if (possibleMoves.empty()) {
        if ((DEPTH + 2) % 2 == WHITE) {
            node.game.setHeuristic(node.game.globalHeuristic(player == WHITE ? BLACK : WHITE));
        } else {
            node.game.setHeuristic(node.game.globalHeuristic(player));
        }
        return node;
    }

    t_playerGame bestMove;
    int nextPlayer = player == WHITE ? BLACK : WHITE;
    if (maximizingPlayer) {
        bestMove.game.setHeuristic(std::numeric_limits<int>::min());
        for (auto& move : possibleMoves) {
            t_playerGame value = miniMax(move, depth - 1, !maximizingPlayer, nextPlayer);
            if (value.game.getHeuristic() > bestMove.game.getHeuristic())
                bestMove = value;
        }
        return bestMove;
    } else {
        bestMove.game.setHeuristic(std::numeric_limits<int>::max());
        for (auto& move : possibleMoves) {
            t_playerGame res = miniMax(move, depth - 1, !maximizingPlayer, nextPlayer);
            if (res.game.getHeuristic() < bestMove.game.getHeuristic())
                bestMove = res;
        }
        return bestMove;
    }
    return bestMove;
}

t_playerGame findBestMove(Game& root, int depth, int player)
{
    int bestValue = std::numeric_limits<int>::min();

    gameSet possibleMoves = generatePossibleMoves(root, player, true, depth);
    t_playerGame bestMove = possibleMoves.front();

    int nextPlayer = player == WHITE ? BLACK : WHITE;
    --depth;
    for (auto& move : possibleMoves) {
        t_playerGame value = miniMax(move, depth, false, nextPlayer);
        if (value.game.getHeuristic() > bestValue) {
            bestValue = value.game.getHeuristic();
            bestMove = move;
        }
    }
    return bestMove;
}