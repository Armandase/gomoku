#include "../inc/utils.hpp"
#include "../inc/Board.hpp"

// return  1 on victory; 0 every in other case
int    place_stone(Board& game, int& player, Render& render, const int& y, const int& x){

    // check if this case isn't already used   
    // if (game.getPos(x, y) != 0){
    if (game.isPosEmpty(x, y) == false){
        std::cout << "Position already used" << std::endl;
        return 1;
    }
    if (game.checkDoubleThree(x, y, player)) {
        std::cout << "DOUBLE THREE X: " << x << " Y: " << y << std::endl;
        return (1);
    }

    game.setPos(x, y, player);
    // gameChecker is used to check if the game is ended or if there is a capture (return 1 on victory)
    int winner = gameChecker(game, y, x, player, render);
    if (winner == 3){ return (1); }
    // select white or black depending of player's color
    if (player == WHITE){
        SDL_SetRenderDrawColor(render.getRenderer(), 255, 255, 255, 255);
        player = BLACK;
    } else {
        SDL_SetRenderDrawColor(render.getRenderer(), 0, 0, 0, 255);
        player = WHITE;
    }
    // draw cirlce... stone, player, pawn, piece ... u know 
    render.drawCircle(x, y);
    if (winner > 0){
        // if someone win, it prints the winner to the screen
        std::string message;
        winner == BLACK ? message = "black wins" : message = "white wins";
        //reset game's board with game's color
        SDL_SetRenderDrawColor(render.getRenderer(), 205, 127, 50, 255);
        SDL_RenderClear(render.getRenderer());

        // select text color and where it should be placed and his size
        SDL_Color textColor = {80, 0, 80, 255};
        SDL_Rect msg_rect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 3, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3};
        render.writeText(message, "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", msg_rect, textColor, 24);
        
        sleep(1);
        game.resetBoard();
        render.render_board();
    }
    return (0);
}

int    handleMouse(Board& game, int& player, Render& render){
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // check if the click is out of the board
    if (mouseX <= MARGIN || mouseX >= SCREEN_WIDTH - MARGIN
        || mouseY <= MARGIN || mouseY >= SCREEN_HEIGHT - MARGIN)
        return (1);

    // get the case corresponding to the click coordinate 
    int x_case = ((mouseX - MARGIN) + GRID_SIZE / 2) / GRID_SIZE;
    int y_case = ((mouseY - MARGIN) + GRID_SIZE / 2) / GRID_SIZE;
    if (x_case > BOARD_SIZE || y_case > BOARD_SIZE)
        return (1);

    // place a stone at the intersection of lines
    if (place_stone(game, player, render, y_case, x_case) > 0)
        return (1);
    return (0);
}
