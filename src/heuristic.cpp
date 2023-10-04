#include "../inc/minMaxAlgorithm.hpp"
#include "../inc/utils.hpp"

int fibo(int n){
    if (n <= 1)
        return n;
    return (fibo(n - 1) + fibo(n - 2));
}

int counterAnalysis(const int count, const bool capture, int empty, int inRow, bool player) {
    int result = 0;

    if (inRow >= 5)
        result = 10000000;
    if ((inRow >= 4 || count >= 5) && empty > 0 )
        result = 5000000;
    if ((inRow == 3 || count >= 4) && empty > 1)
        result = 1000000;
    if ((inRow == 3 || count >= 4) && empty > 0)
        result = 500000;
    if (capture)
        result = 50000;
    if ((inRow == 2 || count >= 3) && empty > 1)
        result = 1000;
    if ((inRow == 2 || count >= 3) && empty > 0)
        result = 500;
    else 
        result = 50 * count + 50 * inRow + empty * 50;
    
    // if (player == false)
    //     result *= -1;
    return (result);
}

bool checkCapture(const vector2d &game, int checkY, int checkX, int dirY, int dirX, int player) {
    int ennemy = (player == WHITE) ? BLACK : WHITE;

    if (checkY + dirY >= 0 && checkY + dirY <= BOARD_SIZE 
        && checkX + dirX >= 0 && checkX + dirX <= BOARD_SIZE
        && game[checkY + dirY][checkX + dirX] == ennemy
        && checkX + dirX * 2 >= 0 && checkX + dirX * 2 <= BOARD_SIZE
        && checkY + dirY * 2 >= 0 && checkY + dirY * 2 <= BOARD_SIZE
        && game[checkY + (dirY * 2)][checkX + (dirX * 2)] == player)
            return true;
    return false;
}

int heuristic(const vector2d &game, int player, const int y, const int x){
    const int   dirX[] = { 0, 1, 0, -1, 1, -1, 1, -1};
    const int   dirY[] = { 1, 0, -1, 0, 1, -1, -1, 1};
    int checkX, checkY, heuristic = 0;

    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
            if (game[y][x] == 0)
                continue ;

            int count[2] = {1}, empty[2] = {0}, inRow[2] = {1};
            bool capture = false, rowChecker[2] = {true}, currentPlayer;
            int newPoint = game[y][x];

            player == newPoint ? currentPlayer = true : currentPlayer = false;
            for (int i = 0; i < 8; i++) {
                for (int j = 1; j < 5; j++) {
                    checkX = x + (dirX[i] * j);
                    checkY = y + (dirY[i] * j);
                    if (checkX < 0 || checkY < 0 || checkX > BOARD_SIZE || checkY > BOARD_SIZE)
                        break ;
                    
                    if (game[checkY][checkX] == newPoint)
                        (count[i % 2])++;
                    if (game[checkY][checkX] == newPoint && rowChecker[i % 2])
                        (inRow[i % 2])++;
                    if (game[checkY][checkX] > 0 && game[checkY][checkX] != newPoint
                        && checkCapture(game, checkY, checkX, dirY[i], dirX[i], newPoint)) {
                        capture = true;
                        break;
                    }
                    else if (game[checkY][checkX] == 0){
                        empty[i % 2]++;
                        rowChecker[i % 2] = false;
                    }
                    else if (game[checkY][checkX] != newPoint && game[checkY][checkX] > 0 )
                        break;
                    
                }
                if (i % 4 < 2){
                    heuristic += counterAnalysis(count[i % 4], capture, empty[i % 4], inRow[i % 4], currentPlayer);
                    count[i % 4] = 1;
                    inRow[i % 4] = 1;
                    empty[i % 4] = 1;
                    capture = false;
                    rowChecker[i % 4] = true;
                }
            }
        }
    }
    return (heuristic);
}