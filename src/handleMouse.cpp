#include "../inc/utils.hpp"
#include "../inc/Board.hpp"


bool posValid(const Board& game, int player, Render& render, int x, int y)
{
    if (x < 0 || x > BOARD_SIZE || y < 0 || y > BOARD_SIZE)
        return false;

    if (game.isPosEmpty(x, y) == false) {
        std::cout << "Position already used" << std::endl;
        return false;
    }

    // check:
    //  - double three

    return true;
}

void place_stone(Board& game, int &player, Render& render, int x, int y)
{
    game.setPos(x, y, player);
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
    //  - win

    // if (winner > 0){
    //     // if someone win, it prints the winner to the screen
    //     std::string message;
    //     winner == BLACK ? message = "black wins" : message = "white wins";
    //     //reset game's board with game's color
    //     SDL_SetRenderDrawColor(render.getRenderer(), 205, 127, 50, 255);
    //     SDL_RenderClear(render.getRenderer());

    //     // select text color and where it should be placed and his size
    //     SDL_Color textColor = {80, 0, 80, 255};
    //     SDL_Rect msg_rect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 3, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3};
    //     render.writeText(message, "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", msg_rect, textColor, 24);
        
    //     sleep(1);
    //     game.resetBoard();
    //     render.render_board();
    // }
}

bool    handleMouse(int mouseX, int mouseY)
{
    if (mouseX <= MARGIN || mouseX >= SCREEN_WIDTH - MARGIN
        || mouseY <= MARGIN || mouseY >= SCREEN_HEIGHT - MARGIN)
        return (false);
    return (true);
}
