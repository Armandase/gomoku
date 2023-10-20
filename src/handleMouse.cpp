#include "../inc/utils.hpp"
#include <unistd.h>


void    place_suggest_stone(int player, SDL_Renderer *renderer, const int y, const int x) {
    if (player == WHITE)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
    else
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    SDL_Rect help = {x * GRID_SIZE + MARGIN - 10, y * GRID_SIZE + MARGIN - 10, 20, 20};
    SDL_RenderFillRect(renderer, &help);
    SDL_RenderPresent(renderer);
}

int    place_stone(vector2d& game, int& player, SDL_Renderer *renderer, const int& y, const int& x, int captureCounter[2]){
    // check if this case isn't already used    
    if (game[y][x] != 0)
        return (1);
    game[y][x] = player;

    // gameChecker is used to check if the game is ended or if there is a capture (return 1 on victory)
    int winner = gameChecker(game, y, x, player, renderer, captureCounter);

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
    if (winner > 0){
        // if someone win, it prints the winner to the screen
        {
            // select corresponding name
            std::string message;
            winner == BLACK ? message = "black wins" : message = "white wins";

            // select text color and where it should be placed and his size
            SDL_Color textColor = {80, 0, 80, 220};
            SDL_Rect msg_rect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 3, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3};
            writeText(message, "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", msg_rect, textColor, 24,renderer);
        }
        sleep(2);
        const int size = game.size();
        for (int i = 0; i < size; i++)
            memset(&game[i][0], 0, game[i].size() * sizeof game[i][0]);
        render_board(renderer);
    }
    return (0);
}

int    handleMouse(vector2d& game, int& player, int captureCounter[2], SDL_Renderer* renderer){
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

    if (place_stone(game, player, renderer, y_case, x_case, captureCounter) > 0)
        return (1);
    return (0);
}
