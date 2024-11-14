#include "../inc/TranspositionTable.hpp"
#include "../inc/algorithm.hpp"

bool isTerminal(Game& node, int player)
{
    return node.playerWin(player) || node.isFull();
}

int miniMax(Game& node, int depth, bool maximizingPlayer, int player)
{
    if (depth == 0 || isTerminal(node, player))
        return node.globalHeurisitic(player);
    int nextPlayer = player == WHITE ? BLACK : WHITE;
    if (maximizingPlayer) {
        int value = std::numeric_limits<int>::min();
        gameSet possibleMoves = generatePossibleMoves(node, player);
        for (auto& move : possibleMoves)
            value = std::max(value, miniMax(move.game, depth - 1, false, nextPlayer));
        return value;
    } else {
        int value = std::numeric_limits<int>::max();
        gameSet possibleMoves = generatePossibleMoves(node, player);
        for (auto& move : possibleMoves)
            value = std::min(value, miniMax(move.game, depth - 1, true, nextPlayer));
        return value;
    }
    return 0;
}

t_playerGame findBestMove(Game& root, int depth, int player)
{
    int bestValue = std::numeric_limits<int>::min();

    gameSet possibleMoves = generatePossibleMoves(root, player);
    t_playerGame bestMove = possibleMoves.front();

    int nextPlayer = player == WHITE ? BLACK : WHITE;
    for (auto& move : possibleMoves) {
        int value = miniMax(move.game, depth, false, nextPlayer);
        // std::cout << "Value: " << value << std::endl;
        if (value > bestValue) {
            bestValue = value;
            bestMove = move;
        }
    }
    return bestMove;
}