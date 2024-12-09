#include "../inc/algorithm.hpp"
#include "../inc/gomoku.hpp"
#include <algorithm>

// IBoard::bitboard getSurroundingBits(Game& game) {
//     IBoard::bitboard surroundingBits = 0;
//     auto firstPlayer = game.getClassicBoard().getPlayer1();
//     auto secondPlayer = game.getClassicBoard().getPlayer2();

//     IBoard::bitboard allPieces = firstPlayer | secondPlayer;
//     int board_size = BOARD_SIZE + 1;

//     IBoard::bitboard leftBoundary = 0;
//     IBoard::bitboard rightBoundary = 0;

//     for (int i = 0; i < board_size; i++) {
//         leftBoundary |= (IBoard::bitboard(1) << (i * board_size));
//         rightBoundary |= (IBoard::bitboard(1) << (i * board_size + board_size
//         - 1));
//     }

//     leftBoundary = ~leftBoundary;
//     rightBoundary = ~rightBoundary;

//     surroundingBits = (allPieces >> board_size) // top
//         | (allPieces << board_size) // bottom
//         | ((allPieces >> 1) & leftBoundary) // left
//         | ((allPieces << 1) & rightBoundary) // right
//         | ((allPieces >> (board_size + 1)) & leftBoundary) // top left
//         | ((allPieces >> (board_size - 1)) & rightBoundary) // top right
//         | ((allPieces << (board_size + 1)) & rightBoundary) // bottom right
//         | ((allPieces << (board_size - 1)) & leftBoundary) // bottom left
//         | allPieces; // center

//     return surroundingBits;
// }

IBoard::bitboard getSurroundingBits(Game& game)
{
    IBoard::bitboard surroundingBits = 0;
    auto firstPlayer = game.getClassicBoard().getPlayer1();
    auto secondPlayer = game.getClassicBoard().getPlayer2();

    IBoard::bitboard allPieces = firstPlayer | secondPlayer;
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
        move.game.setHeuristic(move.game.heuristicTest(move.stone.x, move.stone.y, player));
    }
    std::sort(possibleMoves.begin(), possibleMoves.end(), [](const t_playerGame& a, const t_playerGame& b) {
        return a.game.getHeuristic() > b.game.getHeuristic();
    });
}

gameSet generatePossibleMoves(Game& game, int player)
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
                playerGame.game = std::move(copy);
                possibleMoves.push_back(std::move(playerGame));
            }
        }
    }
    sortBoards(possibleMoves, player);
    if (possibleMoves.size() > PRUNING)
        possibleMoves.resize(PRUNING);
    return possibleMoves;
}

bool isTerminal(Game& node, int player)
{
    return node.playerWin(player) || node.isFull();
}