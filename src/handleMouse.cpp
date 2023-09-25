#include "../inc/gomoku.hpp"


int    place_stone(vector2d& game, int& player, SDL_Renderer *renderer, const int& y, const int& x){
    // check if this case isn't already used    
    if (game[y][x] != 0)
        return (1);
    game[y][x] = player;

    // gameChecker is used to check if the game is ended or if there is a capture (return 1 on victory)
    if (int winner = gameChecker(game, y, x, player, renderer); winner > 0){
        if (winner == BLACK)
            std::cout << "black win" << std::endl;
        else if (winner == WHITE)
            std::cout << "white win" << std::endl;
        // render_board(renderer);
        // game.clear();
        // return (0);
    }

    // select white or black depending of player's color
    if (player == WHITE){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        player = BLACK;
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        player = WHITE;
    }
    // draw cirlce... stone, player, pawn, piece ... u know 
    drawCircle(x, y, renderer);
    return (0);
}

int    handleMouse(vector2d& game, int& player, SDL_Renderer* renderer){
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // check if the click is out of the board
    if (mouseX <= MARGIN || mouseX >= SCREEN_WIDTH - MARGIN
        || mouseY <= MARGIN || mouseY >= SCREEN_HEIGHT - MARGIN)
        return (1);

    // get the case corresponding to the click coordinate 
    int x_case = ((mouseX - MARGIN) + GRID_SIZE / 2) / GRID_SIZE;
    int y_case = ((mouseY - MARGIN) + GRID_SIZE / 2) / GRID_SIZE;
    if (x_case > BOARD_WIDTH || y_case > BOARD_HEIGHT)
        return (1);

    if (place_stone(game, player, renderer, y_case, x_case) > 0)
        return (1);
    return (0);
}