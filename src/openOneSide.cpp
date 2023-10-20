#include "../inc/gomoku.hpp"

bool openSideFour(const vector2d & board, int player, int y, int x) {
    if (board[y][x] == player)
        return false;
    if (x < BOARD_SIZE - 5 &&
        board[y][x + 1] == player &&
        board[y][x + 2] == player && 
        board[y][x + 3] == player &&
        board[y][x + 4] == player &&
        board[y][x + 5] != board[y][x])
        return true;
        
    if (y < BOARD_SIZE - 5 &&
        board[y + 1][x] == player &&
        board[y + 2][x] == player && 
        board[y + 3][x] == player &&
        board[y + 4][x] == player &&
        board[y + 5][x] != board[y][x])
        return true;

    if (x < BOARD_SIZE - 5 && y < BOARD_SIZE - 5 &&
        board[y + 1][x + 1] == player &&
        board[y + 2][x + 2] == player && 
        board[y + 3][x + 3] == player &&
        board[y + 4][x + 4] == player &&
        board[y + 5][x + 5] != board[y][x])
        return true;

    if (x < BOARD_SIZE - 5 && y >= 5 &&
        board[y - 1][x + 1] == player &&
        board[y - 2][x + 2] == player && 
        board[y - 3][x + 3] == player &&
        board[y - 4][x + 4] == player &&
        board[y - 5][x + 5] != board[y][x])
        return true;
    return false;
}

bool openSideThree(const vector2d & board, int player, int y, int x) {
    if (board[y][x] == player)
        return false;
    if (x < BOARD_SIZE - 4 &&
        board[y][x + 1] == player &&
        board[y][x + 2] == player && 
        board[y][x + 3] == player &&
        board[y][x + 4] != board[y][x])
        return true;
        
    if (y < BOARD_SIZE - 4 &&
        board[y + 1][x] == player &&
        board[y + 2][x] == player && 
        board[y + 3][x] == player &&
        board[y + 4][x] != board[y][x])
        return true;

    if (x < BOARD_SIZE - 4 && y < BOARD_SIZE - 4 &&
        board[y + 1][x + 1] == player &&
        board[y + 2][x + 2] == player && 
        board[y + 3][x + 3] == player &&
        board[y + 4][x + 4] != board[y][x])
        return true;

    if (x < BOARD_SIZE - 4 && y >= 4 &&
        board[y - 1][x + 1] == player &&
        board[y - 2][x + 2] == player && 
        board[y - 3][x + 3] == player &&
        board[y - 4][x + 4] != board[y][x])
        return true;
    return false;
}

bool openSideTwo(const vector2d & board, int player, int y, int x) {
    if (board[y][x] == player)
        return false;
    if (x < BOARD_SIZE - 3 &&
        board[y][x + 1] == player &&
        board[y][x + 2] == player && 
        board[y][x + 3] != board[y][x])
        return true;
        
    if (y < BOARD_SIZE - 3 &&
        board[y + 1][x] == player &&
        board[y + 2][x] == player && 
        board[y + 3][x] != board[y][x])
        return true;

    if (x < BOARD_SIZE - 3 && y < BOARD_SIZE - 3 &&
        board[y + 1][x + 1] == player &&
        board[y + 2][x + 2] == player && 
        board[y + 3][x + 3] != board[y][x])
        return true;

    if (x < BOARD_SIZE - 3 && y >= 3 &&
        board[y - 1][x + 1] == player &&
        board[y - 2][x + 2] == player && 
        board[y - 3][x + 3] != board[y][x])
        return true;
    return false;
}