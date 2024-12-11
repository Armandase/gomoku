#include "../inc/Button.hpp"
#include "../inc/Game.hpp"
#include "../inc/Render.hpp"
#include "../inc/algorithm.hpp"
#include "../inc/gomoku.hpp"

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
                if (endgame) {
                    endgame = false;
                    resetGame(game, render, player);
                    continue;
                }
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (!start) {
                    start = modeSelection(game, render, playerButton, IAButton);
                    continue;
                } else if (endgame) {
                    endgame = false;
                    resetGame(game, render, player);
                    continue;
                }
                SDL_GetMouseState(&mouseX, &mouseY);
                if ((player == WHITE || start == PLAYER_MODE) && handleMouse(mouseX, mouseY)) {
                    std::cout << "Empty: " << game.isEmpty() << std::endl;
                    if (start == PLAYER_MODE && game.isEmpty() == false) {
                        t_playerGame gameIA = findBestMovePVS(game, DEPTH, player);
                        // t_playerGame gameIA = findBestMovePVSmultithread(game, DEPTH, player);
                        // t_playerGame gameIA = findBestMove(game, DEPTH, player);
                        placeAdvisorStone(gameIA.stone.x, gameIA.stone.y, render);
                    }
                    int x = coordToBoard(mouseX);
                    int y = coordToBoard(mouseY);
                    if (posValid(game, x, y, player, true)) {
                        game.setPosToBoards(x, y, player);
                        place_stone(game, render, x, y, player, endgame);
                    }
                    if (start == PLAYER_MODE) {
                        t_playerGame gameIA = findBestMovePVS(game, DEPTH, player);
                        // t_playerGame gameIA = findBestMovePVSmultithread(game, DEPTH, player);
                        // t_playerGame gameIA = findBestMove(game, DEPTH, player);
                        placeAdvisorStone(gameIA.stone.x, gameIA.stone.y, render);
                    }
                }
                if (start == IA_MODE && player == BLACK) {
                    timePoint start = std::chrono::high_resolution_clock::now();
                    t_playerGame gameIA = findBestMovePVS(game, DEPTH, player);
                    timePoint end = std::chrono::high_resolution_clock::now();
                    std::cout << "Time taken: "
                              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                              << " milliseconds" << std::endl;
                    // t_playerGame gameIA = findBestMovePVSmultithread(game, DEPTH, player);
                    // t_playerGame gameIA = findBestMove(game, DEPTH, player);

                    // t_playerGame gameIA = iterativeDeepening(game, player);
                    render.renderTime(std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()));
                    place_stone(gameIA.game, render, gameIA.stone.x, gameIA.stone.y,
                        player, endgame);
                    game = gameIA.game;
                }
                SDL_RenderPresent(render.getRenderer());
            }
        }
    }
}
