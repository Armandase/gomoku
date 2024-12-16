#include "../inc/Game.hpp"
#include "../inc/gomoku.hpp"

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

void placeForbiddenMove(Game& game, Render& render, int player)
{
    const int width = game.getClassicBoard().getWidth();
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < width; y++) {
            if (game.getClassicBoard().isPosEmpty(x, y)) {
                render.drawEmptyCase(boardToRender(x), boardToRender(y));
                if (game.isDoubleThree(x, y, player))
                    render.drawRedCross(boardToRender(x), boardToRender(y));
            } 
        }
    }
}

void place_stone(Game& game, Render& render, int x, int y, int& player, bool& endgame)
{
    std::vector<uint16_t> capturesBoard = game.isCapture(x, y, player);
    if (capturesBoard.size() > 0)
        game.handleCapture(x, y, capturesBoard, player, render);

    // draw white or black depending of player's color
    if (player == WHITE)
        SDL_SetRenderDrawColor(render.getRenderer(), 255, 255, 255, 255);
    else
        SDL_SetRenderDrawColor(render.getRenderer(), 0, 0, 0, 255);

#if defined(WHITE_STONE_PATH) && defined(BLACK_STONE_PATH)
    render.drawStoneAssets(boardToRender(x), boardToRender(y), player);
#else
    render.drawCircle(boardToRender(x), boardToRender(y));
#endif

    if (game.playerWin(player)) {
        render.renderWin(player);
        std::cout << "Player " << player << " wins" << std::endl;
        endgame = true;
        return;
    }
    player = (player == WHITE) ? BLACK : WHITE;
    placeForbiddenMove(game, render, player);

// #if defined(PLACING_STONE_SOUND_PATH)
#ifdef PLACING_STONE_SOUND_PATH
    std::string command("paplay " + std::string(PLACING_STONE_SOUND_PATH) + " &");
    system(command.c_str());
#endif
}

void placeAdvisorStone(int x, int y, Render& render)
{
    // SDL_SetRenderDrawColor(render.getRenderer(), LIGHT_GREY_COLOR, LIGHT_GREY_COLOR[1], LIGHT_GREY_COLOR[2], LIGHT_GREY_COLOR[3]);
    SDL_SetRenderDrawColor(render.getRenderer(), LIGHT_GREY_COLOR.r, LIGHT_GREY_COLOR.g, LIGHT_GREY_COLOR.b, LIGHT_GREY_COLOR.a);
    render.drawCircle(boardToRender(x), boardToRender(y));
}

bool handleMouse(int mouseX, int mouseY)
{
    if (mouseX < MARGIN || mouseX > MARGIN + BOARD_DIMENSIONS
        || mouseY < MARGIN || mouseY > MARGIN + BOARD_DIMENSIONS)
        return (false);
    return (true);
}
