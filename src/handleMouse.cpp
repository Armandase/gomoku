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

int checkCaptures(vector2d& game, const int& y_case, const int& x_case, const int& player, SDL_Renderer* renderer){
    const int dirX[] = { 0, 1, 0, -1, 1, -1, 1, -1};
    const int dirY[] = { 1, 0, -1, 0, 1, -1, -1, 1};
    int checkX = 0, checkY = 0;
    
    for (int i = 0; i < 8; i++){
        for (int j = 1; j < 4; j++){
            checkX = x_case + (dirX[i] * j);
            checkY = y_case + (dirY[i] * j);
            if (checkX < 0 || checkY < 0 || checkX > BOARD_HEIGHT || checkY > BOARD_WIDTH)
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


int    handleMouse(vector2d& game, int& player, SDL_Renderer* renderer){
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    if (mouseX <= MARGIN || mouseX >= SCREEN_WIDTH - MARGIN
        || mouseY <= MARGIN || mouseY >= SCREEN_HEIGHT - MARGIN)
        return (1);

    int x_case = ((mouseX - MARGIN) + GRID_SIZE / 2) / GRID_SIZE;
    int y_case = ((mouseY - MARGIN) + GRID_SIZE / 2) / GRID_SIZE;
    if (x_case > BOARD_WIDTH || y_case > BOARD_HEIGHT)
        return (1);
    if (game[y_case][x_case] != 0)
        return (1);
    game[y_case][x_case] = player;
    checkCaptures(game, y_case, x_case, player, renderer);
    if (player == WHITE){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        player = BLACK;
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        player = WHITE;
    }
    drawCircle(x_case, y_case, renderer);
    return (0);
}