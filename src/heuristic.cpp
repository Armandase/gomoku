#include "../inc/utils.hpp"
#include "../inc/MinMax.hpp"

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

bool hasWon(const vector2d & board, int player, int y, int x) {
    if (board[y][x] != player)
        return false;
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
    return false;
}
 
bool openFour(const vector2d & board, int player, int y, int x) {
    if (board[y][x] != 0)
        return false;
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
    return false;
}

bool openThree(const vector2d & board, int player, int y, int x) {
    if (board[y][x] != 0)
        return false;
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
    return false;
}

bool openTwo(const vector2d & board, int player, int y, int x) {
    if (board[y][x] != 0)
        return false;
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
    return false;
}

bool checkCapture(const vector2d &board, int player, int y, int x) {
    int opponent = getOpponent(player);
    if (board[y][x] != player)
        return false;
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
    return false;
}

int heuristic(const vector2d &game, int player, int captures[2]){
    int heuristic = 0;
    int opponent = getOpponent(player);
    for (int y = 0; y <= BOARD_SIZE; y++) {
        for (int x = 0; x <= BOARD_SIZE; x++) {

        if (hasWon(game, player, y, x))
            heuristic += 1000;
        if (hasWon(game, opponent, y, x))
            heuristic -= 1000;

        if (openFour(game, player, y, x))
            heuristic += 500;
        else if (openSideFour(game, player, y, x))
            heuristic += 450;
        if (openFour(game, opponent, y, x))
            heuristic -= 500;
        else if (openSideFour(game, opponent, y, x))
            heuristic -= 450;

        if (checkCapture(game, player, y, x))
            heuristic += 200 * (captures[player - 1] + 1);
        if (checkCapture(game, opponent, y, x))
            heuristic -= 200 * (captures[opponent - 1] + 1);

        if (openThree(game, player, y, x))
            heuristic += 100;
        else if (openSideThree(game, player, y, x))
            heuristic += 90;
        if (openThree(game, opponent, y, x))
            heuristic -= 100;
        else if (openSideThree(game, opponent, y, x))
            heuristic -= 90;

        if (openTwo(game, player, y, x))
            heuristic += 50;
        else if (openSideTwo(game, player, y, x))
            heuristic += 40;

        if (openTwo(game, opponent, y, x))
            heuristic -= 50;
        else if (openSideTwo(game, opponent, y, x))
            heuristic -= 40;
        }
    }
    return (heuristic);
}