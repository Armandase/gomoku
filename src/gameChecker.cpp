#include "../inc/gomoku.hpp"
#include "../inc/utils.hpp"

void    erasePlayer(const int& y_case, const int& x_case, SDL_Renderer* renderer){
    int x_square = x_case * GRID_SIZE + MARGIN - RADIUS;
    int y_square = y_case * GRID_SIZE + MARGIN - RADIUS;

    SDL_SetRenderDrawColor(renderer, 205, 127, 50, 255);
    SDL_Rect rect = {x_square, y_square, RADIUS * 2, RADIUS * 2}; // x, y, width, height
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    int borderX = DIAMETER;
    if (x_square + borderX > MARGIN + (GRID_SIZE * BOARD_SIZE))
        borderX = RADIUS;

    int borderY = DIAMETER;
    if (y_square + borderY > MARGIN + (GRID_SIZE * BOARD_SIZE))
        borderY = RADIUS;

    int startX = 0;
    if (x_square < MARGIN)
        startX = RADIUS;

    int startY = 0;
    if (y_square < MARGIN)
        startY = RADIUS;

    SDL_RenderDrawLine(renderer, x_square + startX , y_square + RADIUS, x_square + borderX, y_square + RADIUS);
    SDL_RenderDrawLine(renderer, x_square + RADIUS, y_square + startY, x_square + RADIUS, y_square + borderY);
    SDL_RenderPresent(renderer);

}

bool checkCapture(const vector2d& game, int checkY, int checkX, int dirY, int dirX, int player) {
    int ennemy = (player == WHITE) ? BLACK : WHITE;

    if (checkY + dirY >= 0 && checkY + dirY <= BOARD_SIZE 
        && checkX + dirX >= 0 && checkX + dirX <= BOARD_SIZE
        && game[checkY + dirY][checkX + dirX] == ennemy
        && checkX + dirX * 2 >= 0 && checkX + dirX * 2 <= BOARD_SIZE
        && checkY + dirY * 2 >= 0 && checkY + dirY * 2 <= BOARD_SIZE
        && game[checkY + (dirY * 2)][checkX + (dirX * 2)] == ennemy
        && checkX + dirX * 3 >= 0 && checkX + dirX * 3 <= BOARD_SIZE
        && checkY + dirY * 3 >= 0 && checkY + dirY * 3 <= BOARD_SIZE
        && game[checkY + (dirY * 3)][checkX + (dirX * 3)] == player)
            return true;
    return false;
}

int gameChecker(vector2d& game, const int& y, const int& x, const int& player, SDL_Renderer* renderer){
    const int   dirX[8] = { 0, 0, 1, -1, 1, -1, 1, -1};
    const int   dirY[8] = { 1, -1, 0, 0, 1, -1, -1, 1};
    int         checkX = x, checkY = y;
    int         count[2] = {1, 1};

    int current = 0;
    for (int i = 0; i < 8; i++){
        if (checkCapture(game, y, x, dirY[i], dirX[i], player) == true){
                erasePlayer(y + dirY[i], x + dirX[i], renderer);
                erasePlayer(y + dirY[i] * 2, x + dirX[i] * 2, renderer);
                game[y + dirY[i]][x + dirX[i]] = 0;
                game[y + dirY[i] * 2][x + dirX[i] * 2] = 0;
                continue ;
        }
        for (int j = 1; j < 5; ++j){
            checkX = x + (dirX[i] * j);
            checkY = y + (dirY[i] * j);
            if (checkX < 0 || checkY < 0 || checkX > BOARD_SIZE || checkY > BOARD_SIZE)
                break ;
            
            if (game[checkY][checkX] != player)
                break ;
            else if (game[checkY][checkX] == player)
                ++(count[i / 2 % 2]);

        }
        if (i % 2 == 1){
            if (count[current] >= 5)
                return (player);
            count[current] = 1;
            (current == 0) ? current = 1 : current = 0;
        }
    }
    if (count[0] >= 5 || count[1] >= 5)
        return (player);
    return 0;
}