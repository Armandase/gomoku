#include "../inc/gomoku.hpp"

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
    // checkCaptures(game, y_case, x_case, player, renderer);
    if (int winner = gameChecker(game, y_case, x_case, player, renderer); winner > 0)
        std::cout << "player " << winner << std::endl;
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