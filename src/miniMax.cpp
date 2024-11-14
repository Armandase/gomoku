#include "../inc/TranspositionTable.hpp"
#include "../inc/algorithm.hpp"

// function minimax(node, depth, maximizingPlayer) is
//     if depth = 0 or node is a terminal node then
//         return the heuristic value of node
//     if maximizingPlayer then
//         value := −∞
//         for each child of node do
//             value := max(value, minimax(child, depth − 1, FALSE))
//     else (* minimizing player *)
//         value := +∞
//         for each child of node do
//             value := min(value, minimax(child, depth − 1, TRUE))
//     return value

bool isTerminal(Game& node, int player) {
  return node.playerWin(player) || node.isFull();
}

int miniMax(Game& node, int depth, bool maximizingPlayer) {
  if (depth == 0 || isTerminal(node, depth % 2))
    return node.globalHeurisitic(depth % 2);
  if (maximizingPlayer) {
    int value = std::numeric_limits<int>::min();
    gameSet possibleMoves = generatePossibleMoves(node, depth % 2);
    for (auto& move : possibleMoves)
      value = std::max(value, miniMax(move.game, depth - 1, false));
    return value;
  } else {
    int value = std::numeric_limits<int>::max();
    gameSet possibleMoves = generatePossibleMoves(node, depth % 2);
    for (auto& move : possibleMoves)
      value = std::min(value, miniMax(move.game, depth - 1, true));
    return value;
  }
  return 0;
}

t_playerGame findBestMove(Game& root, int depth) {
  int bestValue = std::numeric_limits<int>::min();

  gameSet possibleMoves =
      generatePossibleMoves(root, getCurrentPlayer(depth, 0));
  t_playerGame bestMove = possibleMoves.front();
  std::cout << "ALlez le foot" << std::endl;
  std::cout << "Possibles moves" << possibleMoves.size() << std::endl;
  for (auto& move : possibleMoves) {
    int value = miniMax(move.game, depth, false);
    std::cout << "Value: " << value << std::endl;
    if (value > bestValue) {
      bestValue = value;
      bestMove = move;
    }
  }
  std::cout << "Best Value: " << bestValue << std::endl;
  return bestMove;
}