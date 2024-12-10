#include "../inc/Game.hpp"
#include "../inc/utils.hpp"

bool posValid(Game& game, int x, int y, int player, bool verbose)
{
    if (game.getClassicBoard().isPosEmpty(x, y) == false) {
        if (verbose)
            std::cout << "Position already used" << std::endl;
        return false;
    }
    if (!game.canCapture(x, y, player) && game.isDoubleThree(x, y, player)) {
        if (verbose)
            std::cout << "Double Three" << std::endl;
        return false;
    }
    return true;
}

void place_stone(Game& game, Render& render, int x, int y, int& player)
{
    // if (!posValid(game, x, y, player))
    // return;
    // game.setPosToBoards(x, y, player);
    // game.heuristicTest(x, y, player);
    std::vector<uint16_t> capturesBoard = game.isCapture(x, y, player);
    if (capturesBoard.size() > 0)
        game.handleCapture(x, y, capturesBoard, player, render);

    // draw white or black depending of player's color
    if (player == WHITE)
        SDL_SetRenderDrawColor(render.getRenderer(), 255, 255, 255, 255);
    else
        SDL_SetRenderDrawColor(render.getRenderer(), 0, 0, 0, 255);

    render.drawCircle(boardToRender(x), boardToRender(y));

    if (game.playerWin(player)) {
        render.renderWin(player);
        sleep(1);
        game.resetBoards();
        render.renderBoard(game);
        render.eraseCapture();
    }
    player = (player == WHITE) ? BLACK : WHITE;
}

bool handleMouse(int mouseX, int mouseY)
{
    if (mouseX < MARGIN || mouseX > MARGIN + BOARD_DIMENSIONS
        || mouseY < MARGIN || mouseY > MARGIN + BOARD_DIMENSIONS)
        return (false);
    return (true);
}
