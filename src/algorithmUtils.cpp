#include "../inc/algorithm.hpp"

int getCurrentPlayer(int depth, int initPlayer)
{
    if ((depth + 2) % 2 == DEPTH % 2)
        return initPlayer;
    return initPlayer == BLACK ? WHITE : BLACK;
}

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
    int board_size = BOARD_SIZE + 1;

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

gameSet generatePossibleMoves(Game& game, int player)
{
    gameSet possibleMoves;
    IBoard::bitboard neighbour = getSurroundingBits(game);
    int width = game.getClassicBoard().getWidth();
    int nextPlayer = player == BLACK ? WHITE : BLACK;

    for (int y = 0; y < BOARD_SIZE + 1; y++) {
        for (int x = 0; x < BOARD_SIZE + 1; x++) {
            if (game.getClassicBoard().isPosEmpty(x, y) == true && neighbour.test(x + y * width)) {
                Game copy = game;
                copy.setPosToBoards(x, y, nextPlayer);
                // if (validGame(copy, y, x, player) == false)
                // continue;

                // Heuristic h(copy, x, y, x, y);
                // if (checkWin(h) == true){
                // h.setHeuristic(INT_MAX);
                // possibleMoves.insert(h);
                // return possibleMoves;
                // }
                // h.setHeuristic(h.localHeuristic(x, y));
                // possibleMoves.insert(h);
                t_playerGame playerGame;
                playerGame.stone.x = x;
                playerGame.stone.y = y;
                playerGame.stone.player = nextPlayer;
                playerGame.game = copy;
                possibleMoves.push_back(playerGame);
            }
        }
    }
    return possibleMoves;
}