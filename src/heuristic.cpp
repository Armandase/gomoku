#include "../inc/minMaxAlgorithm.hpp"
#include "../inc/utils.hpp"

int fibo(int n){
    if (n <= 1)
        return n;
    return (fibo(n - 1) + fibo(n - 2));
}

int getOpponent(int player) {
    if (player == WHITE)
        return BLACK;
    return WHITE;
}

bool hasWon(const vector2d & board, int player) {
    for (int y = 0; y <= BOARD_SIZE; y++) {
        for (int x = 0; x <= BOARD_SIZE; x++) {
            if (board[y][x] != player)
                continue;
            if (x < BOARD_SIZE - 4 &&
                board[y][x + 1] == player &&
                board[y][x + 2] == player && 
                board[y][x + 3] == player &&
                board[y][x + 4] == player)
                return true;
                
            if (y < BOARD_SIZE - 4 &&
                board[y + 1][x] == player &&
                board[y + 2][x] == player && 
                board[y + 3][x] == player &&
                board[y + 4][x] == player)
                return true;

            if (x < BOARD_SIZE - 4 && y < BOARD_SIZE - 4 &&
                board[y + 1][x + 1] == player &&
                board[y + 2][x + 2] == player && 
                board[y + 3][x + 3] == player &&
                board[y + 4][x + 4] == player)
                return true;

            if (x < BOARD_SIZE - 4 && y >= 4 &&
                board[y - 1][x + 1] == player &&
                board[y - 2][x + 2] == player && 
                board[y - 3][x + 3] == player &&
                board[y - 4][x + 4] == player)
                return true;
        }
    }
    return false;
}

bool openFour(const vector2d & board, int player) {
    for (int y = 0; y <= BOARD_SIZE; y++) {
        for (int x = 0; x <= BOARD_SIZE; x++) {
            if (board[y][x] != 0)
                continue;
            if (x < BOARD_SIZE - 5 &&
                board[y][x + 1] == player &&
                board[y][x + 2] == player && 
                board[y][x + 3] == player &&
                board[y][x + 4] == player &&
                board[y][x + 5] == 0)
                return true;
                
            if (y < BOARD_SIZE - 5 &&
                board[y + 1][x] == player &&
                board[y + 2][x] == player && 
                board[y + 3][x] == player &&
                board[y + 4][x] == player &&
                board[y + 5][x] == 0)
                return true;

            if (x < BOARD_SIZE - 5 && y < BOARD_SIZE - 5 &&
                board[y + 1][x + 1] == player &&
                board[y + 2][x + 2] == player && 
                board[y + 3][x + 3] == player &&
                board[y + 4][x + 4] == player &&
                board[y + 5][x + 5] == 0)
                return true;

            if (x < BOARD_SIZE - 5 && y >= 5 &&
                board[y - 1][x + 1] == player &&
                board[y - 2][x + 2] == player && 
                board[y - 3][x + 3] == player &&
                board[y - 4][x + 4] == player &&
                board[y - 5][x + 5] == 0)
                return true;
        }
    }
    return false;
}

bool openThree(const vector2d & board, int player) {
    for (int y = 0; y <= BOARD_SIZE; y++) {
        for (int x = 0; x <= BOARD_SIZE; x++) {
            if (board[y][x] != 0)
                continue;
            if (x < BOARD_SIZE - 4 &&
                board[y][x + 1] == player &&
                board[y][x + 2] == player && 
                board[y][x + 3] == player &&
                board[y][x + 4] == 0)
                return true;
                
            if (y < BOARD_SIZE - 4 &&
                board[y + 1][x] == player &&
                board[y + 2][x] == player && 
                board[y + 3][x] == player &&
                board[y + 4][x] == 0)
                return true;

            if (x < BOARD_SIZE - 4 && y < BOARD_SIZE - 4 &&
                board[y + 1][x + 1] == player &&
                board[y + 2][x + 2] == player && 
                board[y + 3][x + 3] == player &&
                board[y + 4][x + 4] == 0)
                return true;

            if (x < BOARD_SIZE - 4 && y >= 4 &&
                board[y - 1][x + 1] == player &&
                board[y - 2][x + 2] == player && 
                board[y - 3][x + 3] == player &&
                board[y - 4][x + 4] == 0)
                return true;
        }
    }
    return false;
}

bool openTwo(const vector2d & board, int player) {
    for (int y = 0; y <= BOARD_SIZE; y++) {
        for (int x = 0; x <= BOARD_SIZE; x++) {
            if (board[y][x] != 0)
                continue;
            if (x < BOARD_SIZE - 3 &&
                board[y][x + 1] == player &&
                board[y][x + 2] == player && 
                board[y][x + 3] == 0)
                return true;
                
            if (y < BOARD_SIZE - 3 &&
                board[y + 1][x] == player &&
                board[y + 2][x] == player && 
                board[y + 3][x] == 0)
                return true;

            if (x < BOARD_SIZE - 3 && y < BOARD_SIZE - 3 &&
                board[y + 1][x + 1] == player &&
                board[y + 2][x + 2] == player && 
                board[y + 3][x + 3] == 0)
                return true;

            if (x < BOARD_SIZE - 3 && y >= 3 &&
                board[y - 1][x + 1] == player &&
                board[y - 2][x + 2] == player && 
                board[y - 3][x + 3] == 0)
                return true;
        }
    }
    return false;
}

bool checkCapture(const vector2d &board, int player) {
    int opponent = getOpponent(player);
    for (int y = 0; y <= BOARD_SIZE; y++) {
        for (int x = 0; x <= BOARD_SIZE; x++) {
            if (board[y][x] != player)
                continue;
            if (x < BOARD_SIZE - 3 &&
                board[y][x + 1] == opponent &&
                board[y][x + 2] == opponent && 
                board[y][x + 3] == player)
                return true;
                
            if (y < BOARD_SIZE - 3 &&
                board[y + 1][x] == opponent &&
                board[y + 2][x] == opponent && 
                board[y + 3][x] == player)
                return true;

            if (y < BOARD_SIZE - 3 && x < BOARD_SIZE - 3 &&
                board[y + 1][x + 1] == opponent &&
                board[y + 2][x + 2] == opponent && 
                board[y + 3][x + 3] == player)
                return true;

            if (y >= 3 && x < BOARD_SIZE - 3 &&
                board[y - 1][x + 1] == opponent &&
                board[y - 2][x + 2] == opponent && 
                board[y - 3][x + 3] == player)
                return true;
        }
    }
    return false;
}

int heuristic(const vector2d &game, int player, const int y, const int x){
    int heuristic = 0;
    int opponent = getOpponent(player);
    if (hasWon(game, player))
        heuristic += 1000;
    if (hasWon(game, opponent))
        heuristic -= 1000;

    if (openFour(game, player))
        heuristic += 500;
    else if (openSideFour(game, player))
        heuristic += 450;
    if (openFour(game, opponent))
        heuristic -= 500;
    else if (openSideFour(game, opponent))
        heuristic -= 450;

    if (checkCapture(game, player))
        heuristic += 200;
    if (checkCapture(game, opponent))
        heuristic -= 200;

    if (openThree(game, player))
        heuristic += 100;
    else if (openSideThree(game, player))
        heuristic += 90;
    if (openThree(game, opponent))
        heuristic -= 100;
    else if (openSideThree(game, opponent))
        heuristic -= 90;

    if (openTwo(game, player))
        heuristic += 50;
    else if (openSideTwo(game, player))
        heuristic += 40;

    if (openTwo(game, opponent))
        heuristic -= 50;
    else if (openSideTwo(game, opponent))
        heuristic -= 40;

    return (heuristic);
}