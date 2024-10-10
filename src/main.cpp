#include "../inc/gomoku.hpp"
#include "../inc/utils.hpp"
#include "../inc/Button.hpp"
#include "../inc/Heuristic.hpp"
#include "../inc/Board.hpp"
#include "../inc/minMaxAlgorithm.hpp"
#include "../inc/Render.hpp"

// int main(int argc, char const *argv[])
// {
//     Board test;
//     test.setPos(4, 1, WHITE);
//     test.setPos(5, 1, WHITE);
//     test.setPos(7, 3, WHITE);
//     test.setPos(7, 4, WHITE);

//     // test.setPos(7, 2, BLACK);      
//     int test_col = 7, test_row = 1; // Position to test (the X)
//     if (checkDoubleThree(test._player1, test._player2, test_col, test_row)) {
//         std::cout << "Placing a stone at (" << test_row << ", " << test_col << ") would create a double three!" << std::endl;
//     } else {
//         std::cout << "Placing a stone at (" << test_row << ", " << test_col << ") is allowed." << std::endl;
//     }
//     return 0;
// }

int main()
{
    // try {

    Render render;
    render.init_sdl("Gomoku", SCREEN_WIDTH, SCREEN_HEIGHT);

    int start = 0;
    bool quit = false;
    SDL_Event e;
    int player = WHITE;

    // create 2 button to choose human vs ia or human vs human
    Button playerButton(SCREEN_WIDTH / 3 - 150, SCREEN_HEIGHT / 2 - 50, 300, 100);
    Button IAButton(SCREEN_WIDTH / 3 * 2 - 150, SCREEN_HEIGHT / 2 - 50, 300, 100);

    // Render Start Menu
    start_menu(render, playerButton, IAButton);   

    Board board;
    while (!quit)
    {
        // Handle q and echap for quit the programm
        // If SDL receive an event SDL_PollEvent return 1
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                quit = true;
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q)
                    quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                // if start is equal to 0 then no game mode is chosen
                if (!start)
                {
                    start = handleStart(render, playerButton, IAButton);
                    continue;
                }
                if ((player == WHITE || start == PLAYER_MODE) && handleMouse(board, player, render))
                    continue;
                if (player == BLACK && start == IA_MODE) {
                    minMaxAlgorithm(board, player, render);
                    player = WHITE;
                }
                SDL_RenderPresent(render.getRenderer());
            }
        }
    }
    // } catch (std::exception& e){
        // std::cout << e.what() << std::endl;
    // }
    return 0;
}
