#include "../inc/gomoku.hpp"

int isWin(const vector2d& game, int y, int x){
    const int dirX[] = { 0, 1, 0, -1, 1, -1, 1, -1};
    const int dirY[] = { 1, 0, -1, 0, 1, -1, -1, 1};
    const int player = game[y][x];
    int checkX = 0, checkY = 0;
    
    for (int i = 0; i < 8; i++){
        for (int j = 1; j < 5; j++){
            checkX = x + (dirX[i] * j);
            checkY = y + (dirY[i] * j);
            if (checkX < 0 || checkY < 0 || checkX > 18 || checkY > 18)
                return (0);
            if (game[checkY][checkX] != player)
                break ;
            else if (j == 4)
                return (player);
        }
    }
    return (0);
}

int checkCaptures(vector2d& game, const int& y_case, const int& x_case, const int& player, SDL_Renderer* renderer){
    const int dirX[] = { 0, 1, 0, -1, 1, -1, 1, -1};
    const int dirY[] = { 1, 0, -1, 0, 1, -1, -1, 1};
    int checkX = 0, checkY = 0;
    
    for (int i = 0; i < 8; i++){
        for (int j = 1; j < 4; j++){
            checkX = x_case + (dirX[i] * j);
            checkY = y_case + (dirY[i] * j);
            if (checkX < 0 || checkY < 0 || checkX > 18 || checkY > 18)
                return (0);
            
            if (j == 3 && game[checkY][checkX] == player){
                erasePlayer(checkY - dirY[i], checkX - dirX[i], renderer);
                erasePlayer(checkY - dirY[i] * 2, checkX - dirX[i] * 2, renderer);
                game[checkY - dirY[i]][checkX - dirX[i]] = 0;
                game[checkY - dirY[i] * 2][checkX - dirX[i] * 2] = 0;
                return (player);
            }
            else if (game[checkY][checkX] == player || game[checkY][checkX] == 0)
                break ;
        }
    }
    return (0);
}

int gameChecker(vector2d& game, const int& y_case, const int& x_case, const int& player, SDL_Renderer* renderer){

}