#include "../inc/Button.hpp"
#include "../inc/Game.hpp"
#include "../inc/Render.hpp"
#include "../inc/algorithm.hpp"
#include "../inc/gomoku.hpp"
#include <chrono>
#include <cstdlib>
#include <thread>
void predictPos(Game& game, Render& render, int player, int& lastPosX, int& lastPosY, int x, int y)
{
    t_playerGame gameIA = findBestMovePVS(game, DEPTH, player);
    if (lastPosX != -1 && lastPosY != -1 && !(x == lastPosX && y == lastPosY))
        render.erasePlayer(lastPosX, lastPosY);
    else if (lastPosX == gameIA.stone.x && lastPosY == gameIA.stone.y)
        return;

    lastPosY = gameIA.stone.y;
    lastPosX = gameIA.stone.x;
    placeAdvisorStone(gameIA.stone.x, gameIA.stone.y, render);
}
#include <unistd.h>
// Function to initialize the SDL window and run the game loop
int main()
{
    Render render;
    render.initSDL("Gomoku", SCREEN_WIDTH, SCREEN_HEIGHT);

    int start = 0;
    bool quit = false;
    bool endgame = false;
    SDL_Event e;
    int player = WHITE;
    int mouseX, mouseY;

    // Create buttons for choosing human vs AI or human vs human
    int button_width = 300;
    int button_height = 100;
    Button playerButton(SCREEN_WIDTH / 2 - (button_width / 2), SCREEN_HEIGHT / 2 - button_height, button_width, button_height);
    Button IAButton(SCREEN_WIDTH / 2 - (button_width / 2), SCREEN_HEIGHT / 2 + button_height, button_width, button_height);
    // Button IAButton(SCREEN_WIDTH / 3 * 2 - 150, SCREEN_HEIGHT / 2 - 50, 300, 100);
    Button IAvsIA(SCREEN_WIDTH / 2 - (button_width / 2), SCREEN_HEIGHT / 2 + (button_height * 3), button_width, button_height);
    int lastPosX = -1, lastPosY = -1;
    // Render Start Menu
    // const SDL_Rect PvP = {SCREEN_WIDTH / 3 - 150, SCREEN_HEIGHT / 2 - 50, 300, 100};
    // const SDL_Rect PvIA = {SCREEN_WIDTH / 3 * 2 - 150, SCREEN_HEIGHT / 2 - 50, 300, 100};
    // render.renderImage("img/wlp_go.png", NULL);
    // render.renderImage("img/PvP_Button.png", &PvP);
    // render.renderImage("img/PvP_Button.png", &PvIA);
    // init random
    std::srand((unsigned)time(NULL));
    render.renderMenu(playerButton, IAButton, IAvsIA);
    timePoint lastPlay = std::chrono::high_resolution_clock::now();
    Game game;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                quit = true;
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q)
                    quit = true;
                if (endgame) {
                    resetGame(game, render, player);
                    endgame = false;
                    player = WHITE;
                    start = 0;
                    render.renderMenu(playerButton, IAButton, IAvsIA);
                    continue;
                }
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {

                if (!start) {
                    start = modeSelection(game, render, playerButton, IAButton, IAvsIA);
                    continue;
                } else if (endgame) {
                    resetGame(game, render, player);
                    endgame = false;
                    player = WHITE;
                    start = 0;
                    render.renderMenu(playerButton, IAButton, IAvsIA);
                    continue;
                } else if (start == IA_VS_IA) {
                    continue;
                }
                SDL_GetMouseState(&mouseX, &mouseY);
                if ((player == WHITE || start == PLAYER_MODE) && handleMouse(mouseX, mouseY)) {
                    int x = coordToBoard(mouseX);
                    int y = coordToBoard(mouseY);
                    if (posValid(game, x, y, player, true)) {
                        game.setPosToBoards(x, y, player);
                        place_stone(game, render, x, y, player, endgame);
                    }
                    if (start == PLAYER_MODE)
                        predictPos(game, render, player, lastPosX, lastPosY, x, y);
                }
                if (start == IA_MODE && player == BLACK) {
                    timePoint start = std::chrono::high_resolution_clock::now();
                    // t_playerGame gameIA = findBestMovePVS(game, DEPTH, player);
                    t_playerGame gameIA = findBestMovePVSmultithread(game, DEPTH, player);
                    // t_playerGame gameIA = findBestMove(game, DEPTH, player);
                    // t_playerGame gameIA = iterativeDeepening(game, player);
                    timePoint end = std::chrono::high_resolution_clock::now();
                    render.renderTime(std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()));
                    place_stone(gameIA.game, render, gameIA.stone.x, gameIA.stone.y,
                        player, endgame);
                    game = gameIA.game;
                }
                SDL_RenderPresent(render.getRenderer());
            } else if (start == IA_VS_IA) {
                if (game.isEmpty()) {
                    int x = (std::rand() % BOARD_SIZE) - 1;
                    int y = (std::rand() % BOARD_SIZE) - 1;
                    game.setPosToBoards(x, y, player);
                    place_stone(game, render, x, y, player, endgame);
                    lastPlay = std::chrono::high_resolution_clock::now();
                    continue;
                }
                if (times_up(lastPlay) == false || endgame)
                    continue;
                timePoint start = std::chrono::high_resolution_clock::now();
                t_playerGame gameIA = findBestMovePVS(game, DEPTH, player);
                timePoint end = std::chrono::high_resolution_clock::now();
                render.renderTime(std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()));
                // gameIA.game.setPosToBoards(gameIA.stone.x, gameIA.stone.y, player);
                place_stone(gameIA.game, render, gameIA.stone.x, gameIA.stone.y,
                    player, endgame);
                game = gameIA.game;
                // gameIA.game.setPosToBoards(gameIA.stone.x, gameIA.stone.y, player);
                lastPlay = std::chrono::high_resolution_clock::now();
                SDL_RenderPresent(render.getRenderer());
            }
        }
    }
}