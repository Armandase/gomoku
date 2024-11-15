#include "../inc/TranspositionTable.hpp"
#include "../inc/algorithm.hpp"
#include <future>

t_playerGame miniMax(t_playerGame& node, int depth, bool maximizingPlayer, int player)
{
    if (depth == 0 || isTerminal(node.game, player)) {
        if (DEPTH % 2 == 0) {
            node.game.setHeuristic(node.game.globalHeuristic(player == WHITE ? BLACK : WHITE));
        } else {
            node.game.setHeuristic(node.game.globalHeuristic(player));
        }
        return node;
    }
    gameSet possibleMoves = generatePossibleMoves(node.game, player);
    if (possibleMoves.empty()) {
        if (DEPTH % 2 == 0) {
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

    gameSet possibleMoves = generatePossibleMoves(root, player);
    t_playerGame bestMove = possibleMoves.front();

    int nextPlayer = player == WHITE ? BLACK : WHITE;
    for (auto& move : possibleMoves) {
        t_playerGame value = miniMax(move, depth, false, nextPlayer);
        if (value.game.getHeuristic() > bestValue) {
            bestValue = value.game.getHeuristic();
            bestMove = move;
        }
    }

    std::cout << "Best value: " << bestValue << std::endl;
    // bestMove.game.getClassicBoard().printBoard();
    return bestMove;
}

// t_playerGame findBestMove(Game& root, int depth, int player)
// {
//     std::vector<std::future<t_playerGame>> threadResult;
//     int bestValue = std::numeric_limits<int>::min();

//     gameSet possibleMoves = generatePossibleMoves(root, player);
//     t_playerGame bestMove = possibleMoves.front();

//     int nextPlayer = player == WHITE ? BLACK : WHITE;
//     for (auto& move : possibleMoves) {
//         threadResult.push_back(std::async(std::launch::async, miniMax, std::ref(move), depth, false, nextPlayer));
//     }

//     for (auto& thread : threadResult) {
//         thread.wait();
//         if (thread.valid() == true) {
//             t_playerGame threadReturn = thread.get();
//             if (threadReturn.game.getHeuristic() > bestValue) {
//                 bestValue = threadReturn.game.getHeuristic();
//                 bestMove = threadReturn;
//             }
//         } else {
//             std::cerr << "Fail to join a future" << std::endl;
//         }
//     }

//     std::cout << "Best value: " << bestValue << std::endl;
//     return bestMove;
// }