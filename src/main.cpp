#include "../inc/Button.hpp"
#include "../inc/Game.hpp"
#include "../inc/Render.hpp"
#include "../inc/algorithm.hpp"
#include "../inc/gomoku.hpp"
#include "../inc/utils.hpp"

// Function to initialize the SDL window and run the game loop
int main()
{
    Render render;
    render.initSDL("Gomoku", SCREEN_WIDTH, SCREEN_HEIGHT);

    int start = 0;
    bool quit = false;
    SDL_Event e;
    int player = WHITE;
    int mouseX, mouseY;

    // Create buttons for choosing human vs AI or human vs human
    Button playerButton(SCREEN_WIDTH / 3 - 150, SCREEN_HEIGHT / 2 - 50, 300, 100);
    Button IAButton(SCREEN_WIDTH / 3 * 2 - 150, SCREEN_HEIGHT / 2 - 50, 300, 100);

    // Render Start Menu
    // const SDL_Rect PvP = {SCREEN_WIDTH / 3 - 150, SCREEN_HEIGHT / 2 - 50, 300, 100};
    // const SDL_Rect PvIA = {SCREEN_WIDTH / 3 * 2 - 150, SCREEN_HEIGHT / 2 - 50, 300, 100};
    // render.renderImage("img/wlp_go.png", NULL);
    // render.renderImage("img/PvP_Button.png", &PvP);
    // render.renderImage("img/PvP_Button.png", &PvIA);
    render.renderMenu(playerButton, IAButton);

    Game game;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                quit = true;
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q)
                    quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (!start) {
                    start = modeSelection(game, render, playerButton, IAButton);
                    continue;
                }
                SDL_GetMouseState(&mouseX, &mouseY);
                if ((player == WHITE || start == PLAYER_MODE) && handleMouse(mouseX, mouseY)) {
                    int x = coordToBoard(mouseX);
                    int y = coordToBoard(mouseY);
                    if (posValid(game, x, y, player, true)) {
                        game.setPosToBoards(x, y, player);
                        place_stone(game, render, x, y, player);
                    }
                }
                if (start == IA_MODE && player == BLACK) {
                    t_playerGame gameIA = findBestMovePVS(game, DEPTH, player);
                    // t_playerGame gameIA = findBestMove(game, DEPTH, player);

                    // t_playerGame gameIA = iterativeDeepening(game, player);

                    place_stone(gameIA.game, render, gameIA.stone.x, gameIA.stone.y,
                        player);
                    game = gameIA.game;
                }
                SDL_RenderPresent(render.getRenderer());
            }
        }
    }
}
