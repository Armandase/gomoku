#include "../inc/utils.hpp"
#include "../inc/Game.hpp"


bool posValid(Game& game, int player, int x, int y)
{
    if (game.getClassicBoard().isPosEmpty(x, y) == false) {
        std::cout << "Position already used" << std::endl;
        return false;
    }
    if (game.isDoubleThree(x, y, player)) {
        std::cout << "Double Three" << std::endl;
        return false;
    }
    return true;
}

void place_stone(Game& game, int &player, Render& render, int x, int y)
{
    game.setPosToBoards(x, y, player);
    std::vector<uint16_t> capturesBoard = game.isCapture(x, y, player);
    if (capturesBoard.size() > 0)
        game.handleCapture(x, y, capturesBoard, player, render);
    // draw white or black depending of player's color
    if (player == WHITE)
        SDL_SetRenderDrawColor(render.getRenderer(), 255, 255, 255, 255);
    else
        SDL_SetRenderDrawColor(render.getRenderer(), 0, 0, 0, 255);

    render.drawCircle(x, y);

    if (game.playerWin(player)) {
        std::cout << "PLAYER WIN: " << player << std::endl;
        std::string message;
        player == BLACK ? message = "black wins" : message = "white wins";
        //reset game's Game with game's color
        SDL_SetRenderDrawColor(render.getRenderer(), 205, 127, 50, 255);
        SDL_RenderClear(render.getRenderer());

        // select text color and where it should be placed and his size
        SDL_Color textColor = {80, 0, 80, 255};
        SDL_Rect msg_rect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 3, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3};
        render.writeText(message, "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", msg_rect, textColor, 24);
        
        sleep(1);
        game.resetBoards();
        render.render_board();
    }
    player = player == WHITE ? BLACK : WHITE;
}

bool    handleMouse(int mouseX, int mouseY)
{
    if (mouseX < MARGIN || mouseX > MARGIN + BOARD_DIMENSIONS
        || mouseY < MARGIN || mouseY > MARGIN + BOARD_DIMENSIONS)
        return (false);
    return (true);
}
