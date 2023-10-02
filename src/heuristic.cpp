#include "../inc/minMaxAlgorithm.hpp"
#include "../inc/utils.hpp"

int fibo(int n){
    if (n <= 1)
        return n;
    return (fibo(n - 1) + fibo(n - 2));
}

int counterAnalysis(const int count, const int whiteSpace, const bool capture) {
    if (count == 5)
        return (1000000);
    if (count == 4)
        return (100000);
    if (count == 3)
        return (10000);
    if (capture)
        return (5000);
    if (count == 2)
        return (1000);
    return (100);
}

bool checkCapture(const vector2d &game, int checkY, int checkX, int dirY, int dirX, int player) {
    if (checkY + dirY >= 0 && checkY + dirY <= BOARD_SIZE 
        && checkX + dirX >= 0 && checkX + dirX <= BOARD_SIZE
        && game[checkY + dirY][checkX + dirX] == player
        && checkX + dirX * 2 >= 0 && checkX + dirX * 2 <= BOARD_SIZE
        && checkY + dirY * 2 >= 0 && checkY + dirY * 2 <= BOARD_SIZE
        && game[checkY + dirY * 2][checkX + dirX * 2] != player
        && game[checkY + dirY * 2][checkX + dirX * 2] != 0)
        return true;
    return false;
}

int heuristic(const vector2d &game, int player, const int y, const int x){
    const int   dirX[] = { 0, 1, 0, -1, 1, -1, 1, -1};
    const int   dirY[] = { 1, 0, -1, 0, 1, -1, -1, 1};
    int checkX, checkY;
    int newPoint = game[y][x];
    int count, whiteSpace;
    int heuristic = 0;
    bool capture;

    for (int i = 0; i < 8; i++) {
        count = 1;
        whiteSpace = 0;
        capture = false;
        for (int j = 1; j < 5; j++) {
            checkX = x + (dirX[i] * j);
            checkY = y + (dirY[i] * j);
            if (checkX < 0 || checkY < 0 || checkX > BOARD_SIZE || checkY > BOARD_SIZE)
                break ;
            if (game[checkY][checkX] == newPoint)
                count++;
            else if (game[checkY][checkX] != 0 && checkCapture(game, checkY, checkX, dirY[i], dirX[i], player)) {
                capture = true;
                break;
            }
            else if (game[checkY][checkX] != 0)
                break;
            else 
                whiteSpace++;
        }
        heuristic += counterAnalysis(count, whiteSpace, capture);
    }

    return (heuristic);
}