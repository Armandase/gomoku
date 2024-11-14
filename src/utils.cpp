#include "../inc/gomoku.hpp"

int modeSelection(Game& game, Render& render, Button& player, Button& IA)
{
    int mouseX, mouseY;

    // get the coordinate of the click to know which button has been hit
    SDL_GetMouseState(&mouseX, &mouseY);
    if (player.inButton(mouseX, mouseY)) {
        render.renderBoard(game);
        return PLAYER_MODE;
    }
    if (IA.inButton(mouseX, mouseY)) {
        render.renderBoard(game);
        return IA_MODE;
    }
    return 0;
}

int intlen(int number)
{
    if (number == 0)
        return 1;
    int length = 0;
    while (number != 0) {
        number /= 10;
        length++;
    }
    return length;
}

int coordToBoard(int coor)
{
    return ((coor - MARGIN) + GRID_SIZE / 2) / GRID_SIZE;
}

int boardToRender(int value)
{
    return (value * GRID_SIZE + MARGIN);
}