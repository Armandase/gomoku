#include "../inc/utils.hpp"
#include "../inc/Game.hpp"


bool posValid(const Game& game, int player, Render& render, int x, int y)
{
    if (game.getClassicBoard().isPosEmpty(x, y) == false) {
        std::cout << "Position already used" << std::endl;
        return false;
    }

    // check:
    //  - double three

    return true;
}

void place_stone(Game& game, int &player, Render& render, int x, int y)
{
    game.setPosToBoards(x, y, player);
    // draw white or black depending of player's color
    if (player == WHITE)
        SDL_SetRenderDrawColor(render.getRenderer(), 255, 255, 255, 255);
    else
        SDL_SetRenderDrawColor(render.getRenderer(), 0, 0, 0, 255);
    player = player == WHITE ? BLACK : WHITE;

    render.drawCircle(x, y);

    // check Rules using bit operator if possible
    //  all older check function in gameChecker.cpp but lets do new check 
    //  - capture
    //  - end capture can cancel win
    //  - win

    // if (winner > 0){
    //     // if someone win, it prints the winner to the screen
    //     std::string message;
    //     winner == BLACK ? message = "black wins" : message = "white wins";
    //     //reset game's Game with game's color
    //     SDL_SetRenderDrawColor(render.getRenderer(), 205, 127, 50, 255);
    //     SDL_RenderClear(render.getRenderer());

    //     // select text color and where it should be placed and his size
    //     SDL_Color textColor = {80, 0, 80, 255};
    //     SDL_Rect msg_rect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 3, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3};
    //     render.writeText(message, "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", msg_rect, textColor, 24);
        
    //     sleep(1);
    //     game.resetGame();
    //     render.render_Game();
    // }
}

bool    handleMouse(int mouseX, int mouseY)
{
    if (mouseX < MARGIN || mouseX > MARGIN + BOARD_DIMENSIONS
        || mouseY < MARGIN || mouseY > MARGIN + BOARD_DIMENSIONS)
        return (false);
    return (true);
}
