#include "../inc/gomoku.hpp"

void    erasePlayer(const int& y_case, const int& x_case, SDL_Renderer* renderer){
    int x_square = x_case * GRID_SIZE + MARGIN - RADIUS;
    int y_square = y_case * GRID_SIZE + MARGIN - RADIUS;

    SDL_SetRenderDrawColor(renderer, 205, 127, 50, 255);
    SDL_Rect rect = {x_square, y_square, RADIUS * 2, RADIUS * 2}; // x, y, width, height
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    int borderX = DIAMETER;
    if (x_square + borderX > MARGIN + (GRID_SIZE * BOARD_WIDTH))
        borderX = RADIUS;

    int borderY = DIAMETER;
    if (y_square + borderY > MARGIN + (GRID_SIZE * BOARD_HEIGHT))
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

int gameChecker(vector2d& game, const int& y, const int& x, const int& player, SDL_Renderer* renderer){
    const int   dirX[] = { 0, 1, 0, -1, 1, -1, 1, -1};
    const int   dirY[] = { 1, 0, -1, 0, 1, -1, -1, 1};
    int         checkX = 0, checkY = 0;

    int         result = 0;
    bool        checkWin;
    bool        checkCapture;

    for (int i = 0; i < 8; i++){
        checkWin = true;
        checkCapture = true;
        for (int j = 1; j < 5; j++){
            checkX = x + (dirX[i] * j);
            checkY = y + (dirY[i] * j);
            if (checkX < 0 || checkY < 0 || checkX > 18 || checkY > 18)
                return (0);
            if (checkWin == false && checkCapture == false)
                break ;
            
            if (checkWin == true && game[checkY][checkX] != player)
                checkWin = false;
            else if (checkWin == true && j == 4)
                result = player;
            
            if (checkCapture == true && j == 3 && game[checkY][checkX] == player){
                erasePlayer(checkY - dirY[i], checkX - dirX[i], renderer);
                erasePlayer(checkY - dirY[i] * 2, checkX - dirX[i] * 2, renderer);
                game[checkY - dirY[i]][checkX - dirX[i]] = 0;
                game[checkY - dirY[i] * 2][checkX - dirX[i] * 2] = 0;
            }
            else if (checkCapture == true && (game[checkY][checkX] == player || game[checkY][checkX] == 0))
                checkCapture = false;
        }
    }
    return result;
}