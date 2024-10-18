#include "../inc/gomoku.hpp"
#include "../inc/utils.hpp"
#include "../inc/minMaxAlgorithm.hpp"
#include "../inc/Game.hpp"

bool isCapture(Game& game, int checkY, int checkX, int dirY, int dirX, int player) {
    int ennemy = (player == WHITE) ? BLACK : WHITE;

    if (checkX + dirX * 3 >= 0 && checkX + dirX * 3 <= BOARD_SIZE
        && checkY + dirY * 3 >= 0 && checkY + dirY * 3 <= BOARD_SIZE
        && game.getClassicBoard().getPos(checkX + dirX, checkY + dirY) == ennemy
        && game.getClassicBoard().getPos(checkX + (dirX * 2), checkY + (dirY * 2)) == ennemy
        && game.getClassicBoard().getPos(checkX + (dirX * 3), checkY + (dirY * 3)) == player)
            return true;
    return false;
}

// bool Game::checkPossibleCapture(uint16_t x, uint16_t y, uint16_t player) {
//     int opponent = (player == WHITE) ? BLACK : WHITE;

//     int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {1, -1}, {-1, 1}};

//     for (int i = 0; i < 4; ++i) {
//         int x1 = x + directions[i * 2][0], y1 = y + directions[i * 2][1];
//         int x2 = x + directions[i * 2 + 1][0], y2 = y + directions[i * 2 + 1][1];
//         int x3 = x2 + directions[i * 2 + 1][0], y3 = y2 + directions[i * 2 + 1][1];

//         if (getClassicBoard().isValidPos(x1, y1)
//         && getClassicBoard().isValidPos(x2, y2)
//         && getClassicBoard().isValidPos(x3, y3)) {
//             if (getClassicBoard().getPos(x1, y1) == opponent
//             && getClassicBoard().getPos(x2, y2) == player
//             && getClassicBoard().getPos(x3, y3) == 0)
//                 return true;

//             if (getClassicBoard().getPos(x1, y1) == 0 
//             && getClassicBoard().getPos(x2, y2) == player 
//             && getClassicBoard().getPos(x3, y3) == opponent)
//                 return true;
//         }
//     }
//     return false;
// }
// int gameChecker(Game& game, int y, int x, int player, Render& render){
//     const int   dirX[8] = { 0, 0, 1, -1, 1, -1, 1, -1};
//     const int   dirY[8] = { 1, -1, 0, 0, 1, -1, -1, 1};
//     int         checkX = x, checkY = y;
//     int         count[2] = {1, 1};

//     // game.printBoard();
//     int current = 0;
//     for (int i = 0; i < 8; i++){
//         if (isCapture(game, y, x, dirY[i], dirX[i], player) == true){
//             render.erasePlayer(y + dirY[i], x + dirX[i]);
//             render.erasePlayer(y + dirY[i] * 2, x + dirX[i] * 2);
//             game.removePosToBoards(x + dirX[i], y + dirY[i]);
//             game.removePosToBoards(x + dirX[i] * 2, y + dirY[i] * 2);
//             game.addCapture(player);
//             if (game.getCapture(player) == 5)
//                 return (player);
//             continue ;
//         }
//         if (!checkPossibleCapture(game, x, y, player)) {
//             for (int j = 1; j < 5; ++j){
//                     break ;
                
//                 if (game.getClassicBoard().getPos(checkX, checkY) != player)
//                     break ;

//                 if (game.getClassicBoard().getPos(checkX, checkY) == player && !checkPossibleCapture(game, checkX, checkY, player))
//                     ++(count[i / 2 % 2]);
//             }

//             if (i % 2 == 1){
//                 if (count[current] >= 5)
//                     return (player);
//                 count[current] = 1;
//                 (current == 0) ? current = 1 : current = 0;
//             }
//         }
//     }
//     if (count[0] >= 5 || count[1] >= 5)
//         return (player);
//     return 0;
// }

// bool doubleThree(const Game& game, int x, int y, int player){ 
//     patternBitset close_doubleThree("1100"); 
//     patternBitset distant_doubleThree("0110"); 
//     int double_three = 0;

//      getter de tout les patterns
    // Board::patternMap patterns = game.extractPatterns(x, y, 3, player);
//     patterns.merge(game.extractPatternsReversed(x, y, 3, player));

//     for (auto const& [key, val] : patterns){
//         if ((val & close_doubleThree) == close_doubleThree)
//             double_three++;
//         else if ((val & distant_doubleThree) == distant_doubleThree)
//             double_three++;

//         if (double_three >= 2){
//             return true;
//         }
//     }
//     return false;
// }