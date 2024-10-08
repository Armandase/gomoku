#include "../inc/gomoku.hpp"
#include "../inc/utils.hpp"
#include "../inc/minMaxAlgorithm.hpp"
#include "../inc/Button.hpp"
#include "../inc/Heuristic.hpp"
#include "../inc/Board.hpp"

// render the board base on the number of square and them size
void render_board(SDL_Renderer *renderer)
{
    // select brown color and clear the board with this color
    SDL_SetRenderDrawColor(renderer, 205, 127, 50, 255);
    SDL_RenderClear(renderer);
    //select black color to draw lines
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Draw grid of Board size + 1 ^ 2
    int line = BOARD_SIZE * (GRID_SIZE + 1);
    for (int x = MARGIN, i = 0; x < line + GRID_SIZE && i <= BOARD_SIZE; x += GRID_SIZE, i++)
    {
        // draw line on x and y axis
        SDL_RenderDrawLine(renderer, x, MARGIN, x, line);
        SDL_RenderDrawLine(renderer, MARGIN, x, line , x);
    }
    //render the board
    SDL_RenderPresent(renderer);
}

// int main(int argc, char const *argv[])
// {
//     Board test;
//     test.setPos(4, 1, WHITE);
//     test.setPos(5, 1, WHITE);
//     test.setPos(7, 3, WHITE);
//     test.setPos(7, 4, WHITE);

//     // test.setPos(7, 2, BLACK);      
//     int test_col = 7, test_row = 1; // Position to test (the X)
//     if (check_double_free_three(test._player1, test._player2, test_col, test_row)) {
//         std::cout << "Placing a stone at (" << test_row << ", " << test_col << ") would create a double three!" << std::endl;
//     } else {
//         std::cout << "Placing a stone at (" << test_row << ", " << test_col << ") is allowed." << std::endl;
//     }
//     return 0;
// }

int main()
{
    //init sdl variables
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        SDL_Error("Failed to init SDL:", NULL, NULL);
    if (TTF_Init() == -1)
        SDL_Error("Failed to init TTF:", NULL, NULL);
    SDL_Window *window = SDL_CreateWindow("Gomoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
        SDL_Error("Failed to create SDL window:", window, NULL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        SDL_Error("Failed to create SDL renderer:", window, renderer);

    int start = 0;
    bool quit = false;
    SDL_Event e;
    int player = WHITE;

    // create 2 button to choose human vs ia or human vs human
    Button playerButton(SCREEN_WIDTH / 3 - 150, SCREEN_HEIGHT / 2 - 50, 300, 100);
    Button IAButton(SCREEN_WIDTH / 3 * 2 - 150, SCREEN_HEIGHT / 2 - 50, 300, 100);

    // Render Start Menu
    start_menu(renderer, playerButton, IAButton);   

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
                    start = handleStart(renderer, playerButton, IAButton);
                    continue;
                }
                if (player == WHITE && handleMouse(board, player, renderer))
                    continue;
                if (player == BLACK) {
                    minMaxAlgorithm(board, player, renderer);
                    player = WHITE;
                }
                SDL_RenderPresent(renderer);
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
