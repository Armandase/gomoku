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

void printBoard(const std::vector<std::vector<std::string>>& board) {
    for (const auto& row : board) {
        for (const auto& element : row) {
            std::cout << (element.empty() ? "   " : element + " ");
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<std::string>> rotateBoard45Degrees(const std::vector<std::vector<std::string>>& board) {
    int rows = board.size();
    int cols = board[0].size();
    int newSize = rows;  // Keeping the original row count

    // Create a new result board initialized with empty strings
    std::vector<std::vector<std::string>> result(newSize, std::vector<std::string>(cols, ""));

    // Place elements in a way that each diagonal is filled according to the desired rotation
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int newRow = (row + col) % rows; // Shifting row positions by sum of row and column
            int newCol = col;                // Keep the same column
            result[newRow][newCol] = board[row][col];
        }
    }

    return result;
}

std::vector<std::vector<std::string>> rotateBoard45DegreesCounterClockwise(const std::vector<std::vector<std::string>>& board) {
    int rows = board.size();
    int cols = board[0].size();
    int newSize = rows;  // Keeping the original row count

    // Create a new result board initialized with empty strings
    std::vector<std::vector<std::string>> result(newSize, std::vector<std::string>(cols, ""));

    // Place elements in a way that each diagonal is filled according to the counterclockwise rotation
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            // For counterclockwise rotation, subtract col from row
            int newRow = (row - col + rows) % rows; // Handle negative indices with +rows
            int newCol = col; // Keep the column index unchanged
            result[newRow][newCol] = board[row][col];
        }
    }

    return result;
}

// int main() {
//     std::vector<std::vector<std::string>> board = {
//         {"A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8"},
//         {"A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7"},
//         {"A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6"},
//         {"A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5"},
//         {"A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4"},
//         {"A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3"},
//         {"A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2"},
//         {"A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1"}
//     };

//     std::cout << "Original Board:\n";
//     printBoard(board);
//     std::cout << "\nRotated Board 45:\n";
//     std::vector<std::vector<std::string>> rotatedBoard = rotateBoard45Degrees(board);
//     printBoard(rotatedBoard);

//     std::cout << "\nRotated Board 315:\n";
//     std::vector<std::vector<std::string>> rotatedBoardCounter = rotateBoard45DegreesCounterClockwise(board);
//     printBoard(rotatedBoardCounter);
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
