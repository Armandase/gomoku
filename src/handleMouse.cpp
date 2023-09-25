#include "../inc/gomoku.hpp"
#include <unistd.h>

void print_game(const vector2d& game) {
    const int game_size = game.size();
    for (int i = 0; i < game_size; i++) {
        for (int j = 0; j < game_size; j++)
            std::cout << game[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int    place_stone(vector2d& game, int& player, SDL_Renderer *renderer, const int& y, const int& x){
    // check if this case isn't already used    
    if (game[y][x] != 0)
        return (1);
    game[y][x] = player;

    int winner = gameChecker(game, y, x, player, renderer);
    // gameChecker is used to check if the game is ended or if there is a capture (return 1 on victory)


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
        std::string message;
        if (winner == BLACK)
            message = "black wins";
        else if (winner == WHITE)
            message = "white wins";
        {
            SDL_SetRenderDrawColor(renderer, 205, 127, 50, 255);
            SDL_RenderClear(renderer);
            TTF_Font* Sans = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
            SDL_Color white = {80, 0, 80, 255};
            SDL_Surface* surfaceMsg = TTF_RenderText_Solid(Sans, message.c_str(), white);
            SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMsg);
            SDL_Rect Message_rect;
            Message_rect.x = SCREEN_WIDTH / 4; 
            Message_rect.y = SCREEN_HEIGHT / 3;
            Message_rect.w = SCREEN_WIDTH / 2;
            Message_rect.h = Message_rect.y;
            SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
            SDL_RenderPresent(renderer);
            SDL_FreeSurface(surfaceMsg);
            SDL_DestroyTexture(Message);
        }
        sleep(2);        
        for (int i = 0; i < game.size(); i++)
            memset(&game[i][0], 0, game[i].size() * sizeof game[i][0]);
        // print_game(game);
        render_board(renderer);
    }
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