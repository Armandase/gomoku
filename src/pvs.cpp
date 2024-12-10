#include "../inc/algorithm.hpp"
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

int pvs(t_playerGame& node, int alpha, int beta, int depth, int maxNode)
{
    const int opponent = (node.stone.player == WHITE) ? BLACK : WHITE;
    if (depth <= 0 || isTerminal(node.game, node.stone.player)) {
        if (maxNode)
            return node.game.heuristicTest(node.stone.x, node.stone.y, node.stone.player);
        else
            return -node.game.heuristicTest(node.stone.x, node.stone.y, node.stone.player);
    }
    int nextPlayer = node.stone.player == WHITE ? BLACK : WHITE;
    gameSet possibleMoves = generatePossibleMoves(node.game, nextPlayer, !maxNode);
    int score = 0;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); ++it) {
        if (it == possibleMoves.begin())
            score = -pvs(*it, -beta, -alpha, depth - 1, !maxNode);
        else {
            score = -pvs(*it, -alpha - 1, -alpha, depth - 1, !maxNode);
            if (alpha < score && score < beta)
                score = -pvs(*it, -beta, -alpha, depth - 1, !maxNode);
        }
        alpha = std::max(alpha, score);
        if (alpha >= beta)
            break;
    }
    return alpha;
}

t_playerGame findBestMovePVS(Game& root, int depth, int player)
{
    gameSet possibleMoves = generatePossibleMoves(root, player, true);
    if (possibleMoves.empty()) {
        t_playerGame playerGame;
        playerGame.game = root;
        playerGame.stone.player = player;
        return playerGame;
    }

    int nextPlayer = player == WHITE ? BLACK : WHITE;
    int bestValue = std::numeric_limits<int>::min();
    t_playerGame bestMove = possibleMoves.front();

    --depth;
    int result = std::numeric_limits<int>::min();
    for (auto& move : possibleMoves) {
        result = pvs(move,
            std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), depth, true);
        if (result > bestValue) {
            bestValue = result;
            bestMove = move;
        }
    }

    // std::cout << "Best value: " << bestValue << std::endl;
    // bestMove.game.getClassicBoard().printBoard();
    return bestMove;
}