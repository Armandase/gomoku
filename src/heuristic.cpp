#include "../inc/minMaxAlgorithm.hpp"
#include "../inc/utils.hpp"
// void scoreUpdate(const int &playerCount, const int &opponentCount, int &score) {
//     if (playerCount == 5) {
//         score = INT_MAX;
//         return ;
//     }
//     else if (playerCount == 4 && opponentCount == 0)
//         score += 1000;
//     else if (playerCount == 3 && opponentCount == 0)
//         score += 100;
//     else if (playerCount == 2 && opponentCount == 0)
//         score += 10;
//     else if (playerCount == 1 && opponentCount == 0)
//         score += 1;
// }

// void scoreLine(const vector2d &game, int player, int y, int x, int &score) {
//     int playerCount = 0;
//     int opponentCount = 0;
    
//     for (int k = 0; k < 5; ++k) {
//         if (game[y][x + k] == player) {
//             playerCount++;
//         } else if (game[y][x + k] != 0) {
//             opponentCount++;
//         }
//     }
//     scoreUpdate(playerCount, opponentCount, score);
// }

// void scoreColumns(const vector2d &game, int player, int y, int x, int &score) {
//     int playerCount = 0;
//     int opponentCount = 0;
    
//     for (int k = 0; k < 5; ++k) {
//         if (game[y + k][x] == player) {
//             playerCount++;
//         } else if (game[y + k][x] != 0) {
//             opponentCount++;
//         }
//     }
//     scoreUpdate(playerCount, opponentCount, score);
// }

// int heuristic(const vector2d &game, int player) {
//     int heuristic = 0;
//     for (int y = 0; y < BOARD_SIZE + 1; ++y) {
//         for (int x = 0; x < BOARD_SIZE + 1; ++x) {
//             if (x + 4 < BOARD_SIZE + 1) {
//                 scoreLine(game, player, y, x, heuristic);
//                 if (heuristic == INT_MAX)
//                     return heuristic;
//             }
//             if (y + 4 < BOARD_SIZE + 1) {
//                 scoreColumns(game, player, y, x, heuristic);
//                 if (heuristic == INT_MAX)
//                     return heuristic;
//             }
//         }
//     }
//     return heuristic;
// }
int counterAnalysis(const int counter, const int player, const int color){
    int result = 0;

    if (counter == 5 && player == color)
        result = 1000;
    else if (counter == 5 && player != color)
        result = 1000;
    else if (counter == 4 && player != color)
        result = 600;
    else if (counter == 4 && player == color)
        result = 500;
    else if (counter != 3)
        result = 250;
    else if (counter == 3)
        result = 250;
    else
        result = counter * 100;
    return (result);
}

int heuristic(const vector2d &game, int player, const int y, const int x){
    const int   dirX[] = { 0, 1, 0, -1, 1, -1, 1, -1};
    const int   dirY[] = { 1, 0, -1, 0, 1, -1, -1, 1};
    int         checkX = 0, checkY = 0;
    int         counter, color, heuristic = 0;

    for (int i = 0; i < 8; i++){
        counter = 1;
        color = 0;
        for (int j = 1; j < 5; j++){
            checkX = x + (dirX[i] * j);
            checkY = y + (dirY[i] * j);
            if (checkX < 0 || checkY < 0 || checkX > BOARD_SIZE || checkY > BOARD_SIZE || game[checkY][checkX] == 0)
                break ;
            if (j == 1)
                color = game[checkY][checkX];
            if (game[checkY][checkX] == color && counter + 1 < 5)
                counter++;
            else
                break ;
        }
        if (color)
            heuristic += counterAnalysis(counter + 1, player, color);
    }
    // std::cout << "HEURISITIC: " << heuristic << "\n";
    return (heuristic);
}