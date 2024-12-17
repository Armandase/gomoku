#include "../inc/Button.hpp"
#include "../inc/Game.hpp"
#include "../inc/Render.hpp"
#include "../inc/algorithm.hpp"
#include "../inc/gomoku.hpp"
#include <chrono>
#include <cstdlib>
#include <thread>
#include <unistd.h>

// Function used in PvP mode to advise the player where to play
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
// Function to initialize the SDL window and run the game loop
int main()
{
    Render render;
    render.initSDL("Gomoku", SCREEN_WIDTH, SCREEN_HEIGHT);

    int start = 0;
    bool quit = false;
    bool endgame = false;
    SDL_Event e;
    int player = BLACK;
    int mouseX, mouseY;

    // Create buttons for choosing human vs AI or human vs human
    int button_width = 300;
    int button_height = 100;
    int posX = SCREEN_WIDTH / 2 - (button_width / 2);
    int nbWidgets = 6;
    int heightPerWidget = (SCREEN_HEIGHT / nbWidgets + 1);
    // lambda function to compute the position in y
    auto computeY = [&](int i) {
        return i * heightPerWidget;
    };

    Button playerButton(posX, computeY(1), button_width, button_height);
    Button IAButton(posX, computeY(2), button_width, button_height);
    Button IAvsIA(posX, computeY(3), button_width, button_height);
    Button PvPPro(posX, computeY(4), button_width, button_height);
    Button PvPLongPro(posX, computeY(5), button_width, button_height);
    std::vector<std::tuple<Button, std::string>> buttons = {
        { playerButton, "Player VS Player" },
        { IAButton, "Player VS IA" },
        { IAvsIA, "IA VS IA" },
        { PvPPro, "PvP Pro Mode" },
        { PvPLongPro, "PvP Long Pro Mode" }
    };
    render.renderMenu(buttons);
    int lastPosX = -1, lastPosY = -1;
    // Render Start Menu
    // const SDL_Rect PvP = {SCREEN_WIDTH / 3 - 150, SCREEN_HEIGHT / 2 - 50, 300, 100};
    // const SDL_Rect PvIA = {SCREEN_WIDTH / 3 * 2 - 150, SCREEN_HEIGHT / 2 - 50, 300, 100};
    // render.renderImage("img/wlp_go.png", NULL);
    // render.renderImage("img/PvP_Button.png", &PvP);
    // render.renderImage("img/PvP_Button.png", &PvIA);
    // init random
    std::srand((unsigned)time(NULL));
    timePoint lastPlay = std::chrono::high_resolution_clock::now();
    Game game;
    int nbTurn = 0;
    int timeSum = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                quit = true;
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q)
                    quit = true;
                if (endgame) {
                    resetGame(game, render);
                    endgame = false;
                    player = BLACK;
                    if (start == IA_MODE) {
                        std::cout << "Average time for IA to play " << timeSum / (nbTurn / 2) << " ms" << std::endl;
                    }
                    start = 0;
                    nbTurn = 0;
                    timeSum = 0;
                    render.renderMenu(buttons);
                    continue;
                }
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {

                if (!start) {
                    start = modeSelection(game, render, playerButton, IAButton, IAvsIA, PvPPro, PvPLongPro);
                    continue;
                } else if (endgame) {
                    resetGame(game, render);
                    endgame = false;
                    player = BLACK;
                    if (start == IA_MODE) {
                        std::cout << "Average time for IA to play " << timeSum / (nbTurn / 2) << " ms" << std::endl;
                    }
                    start = 0;
                    nbTurn = 0;
                    timeSum = 0;
                    render.renderMenu(buttons);
                    continue;
                } else if (start == IA_VS_IA) {
                    continue;
                }
                SDL_GetMouseState(&mouseX, &mouseY);
                if (((player == WHITE && start == IA_MODE) || start == PLAYER_MODE || start == PVP_PRO || start == PVP_LONGPRO) && handleMouse(mouseX, mouseY)) {
                    int x = coordToBoard(mouseX);
                    int y = coordToBoard(mouseY);
                    if (nbTurn == 0 && (start == PVP_PRO || start == PVP_LONGPRO)) {
                        x = (BOARD_SIZE - 1) / 2;
                        y = (BOARD_SIZE - 1) / 2;
                    } else if (nbTurn == 2 && start == PVP_PRO) {
                        int centerX = (BOARD_SIZE - 1) / 2;
                        int centerY = (BOARD_SIZE - 1) / 2;
                        if (x > centerX - 3 && x < centerX + 3 && y > centerY - 3 && y < centerY + 3) {

                            continue;
                        }
                    } else if (nbTurn == 2 && start == PVP_LONGPRO) {
                        int centerX = (BOARD_SIZE - 1) / 2;
                        int centerY = (BOARD_SIZE - 1) / 2;
                        if (x > centerX - 4 && x < centerX + 4 && y > centerY - 4 && y < centerY + 4) {
                            continue;
                        }
                    }
                    if (posValid(game, x, y, player, true)) {
                        game.setPosToBoards(x, y, player);
                        place_stone(game, render, x, y, player, endgame);
                    }
                    if (start == PLAYER_MODE)
                        predictPos(game, render, player, lastPosX, lastPosY, x, y);
                    nbTurn++;
                }
                if (start == IA_MODE && player == BLACK) {
                    if (game.isEmpty()) {
                        int x = BOARD_SIZE / 2;
                        int y = BOARD_SIZE / 2;
                        game.setPosToBoards(x, y, player);
                        place_stone(game, render, x, y, player, endgame);
                        player = WHITE;
                        continue;
                    }
                    timePoint start = std::chrono::high_resolution_clock::now();
                    // t_playerGame gameIA = findBestMovePVS(game, DEPTH, player);
                    t_playerGame gameIA = findBestMovePVSmultithread(game, DEPTH, player);
                    //  t_playerGame gameIA = findBestMove(game, DEPTH, player);
                    timePoint end = std::chrono::high_resolution_clock::now();
                    int diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                    timeSum += diff;
                    render.renderTime(std::to_string(diff));
                    place_stone(gameIA.game, render, gameIA.stone.x, gameIA.stone.y,
                        player, endgame);
                    game = gameIA.game;
                    nbTurn++;
                    std::cout << "IA played " << nbTurn / 2 << " times" << std::endl;
                }
                SDL_RenderPresent(render.getRenderer());
            }
        }
        if (start == IA_VS_IA) {
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
            place_stone(gameIA.game, render, gameIA.stone.x, gameIA.stone.y,
                player, endgame);
            game = gameIA.game;
            lastPlay = std::chrono::high_resolution_clock::now();
            nbTurn++;
        }
    }
}