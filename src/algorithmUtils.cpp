#include "../inc/algorithm.hpp"
#include "../inc/gomoku.hpp"
#include <algorithm>

IBoard::bitboard getSurroundingBits(Game& game)
{
    IBoard::bitboard surroundingBits = 0;
    int board_size = BOARD_SIZE;

    const int dir[8][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 },
        { 1, 1 }, { -1, -1 }, { 1, -1 }, { -1, 1 } };

    for (int y = 0; y < board_size; y++) {
        for (int x = 0; x < board_size; x++) {
            if (game.getClassicBoard().isPosEmpty(x, y) == true)
                continue;

            for (int i = 0; i < 8; i++) {
                int checkX = x + dir[i][0];
                int checkY = y + dir[i][1];
                if (checkX < 0 || checkY < 0 || checkX >= board_size || checkY >= board_size)
                    continue;

                surroundingBits |= (IBoard::bitboard(1) << (checkX + checkY * board_size));
            }
            surroundingBits |= (IBoard::bitboard(1) << (x + y * board_size));
        }
    }

    return surroundingBits;
}

void sortBoards(gameSet& possibleMoves, int player)
{
    for (auto& move : possibleMoves) {
        move.game.setHeuristic(move.game.heuristicLocal(move.stone.x, move.stone.y, player));
    }
    std::sort(possibleMoves.begin(), possibleMoves.end(), [](const t_playerGame& a, const t_playerGame& b) {
        return a.game.getHeuristic() > b.game.getHeuristic();
    });
}

gameSet generatePossibleMoves(Game& game, int player, bool max, int depth)
{
    gameSet possibleMoves;
    IBoard::bitboard neighbourBits = getSurroundingBits(game);
    int width = game.getClassicBoard().getWidth();

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            int bitIndex = x + y * width;

            if (game.getClassicBoard().isPosEmpty(x, y) == false || !neighbourBits.test(bitIndex))
                continue;

            if (posValid(game, x, y, player)) {
                Game copy = game;
                copy.setPosToBoards(x, y, player);

                t_playerGame playerGame;
                playerGame.stone.x = x;
                playerGame.stone.y = y;
                playerGame.stone.player = player;
                playerGame.depth = depth;
                playerGame.game = std::move(copy);
                possibleMoves.push_back(std::move(playerGame));
            }
        }
    }
    sortBoards(possibleMoves, player);
    if (possibleMoves.size() > PRUNING && max)
        possibleMoves.resize(PRUNING);
    else if (possibleMoves.size() > PRUNING)
        possibleMoves.erase(possibleMoves.begin(), possibleMoves.end() - PRUNING);
    else
        (void)0;

    return possibleMoves;
}

bool isTerminal(Game& node, int player)
{
    return node.playerWin(player) || node.isFull();
}

bool times_up(const timePoint& start)
{
    const timePoint now = std::chrono::high_resolution_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() >= TIME_UP) {
        return true;
    }
    return false;
}
