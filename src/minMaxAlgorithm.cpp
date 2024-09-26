#include "../inc/minMaxAlgorithm.hpp"
#include "../inc/utils.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <future>
# include <set>

bool emptyNeighbour(const Board &game, const int x, const int y){
    const int   dirX[] = { 0, 0, 1, -1, 1, -1, 1, -1};
    const int   dirY[] = { 1, -1, 0, 0, 1, -1, -1, 1};
    int         checkX = 0, checkY = 0;
    int         counter = 0;

    for (int i = 0; i < 8; i++){
        checkX = x + dirX[i];
        checkY = y + dirY[i];
        if (checkX < 0 || checkY < 0 || checkX > BOARD_SIZE || checkY > BOARD_SIZE){
            counter++;
            continue;
        }
        if (game.isPosEmpty(checkX, checkY) == true)
            counter++;        
    }
    if (counter == 8)
        return (true);
    return (false);
}

Heuristic finCorrectValue(const heuristicSet& recursiveResult, int minOrMax){
    if (recursiveResult.empty())
        throw std::runtime_error("Empty vector of recursive\n");
    // for (auto it = recursiveResult.begin(); it != recursiveResult.end(); it++){
    //     std::cout << it->getHeuristic() << "\n";
    // }
    if (minOrMax == MAX){
        // std::cout << "max: " << recursiveResult.rbegin()->getHeuristic() << "\n";
        return *recursiveResult.rbegin();
    }
    // std::cout << "min: " << recursiveResult.begin()->getHeuristic() << "\n";
    return *recursiveResult.begin();
}

bool checkWin(const Board& game, const int& y, const int& x, const int& player){
    const int   dirX[] = { 0, 0, 1, -1, 1, -1, 1, -1};
    const int   dirY[] = { 1, -1, 0, 0, 1, -1, -1, 1};
    int         checkX = 0, checkY = 0;
    int         count[2] = {1, 1};

    int current = 0;
    for (int i = 0; i < 8; i++){
        for (int j = 1; j < 5; j++){
            checkX = x + (dirX[i] * j);
            checkY = y + (dirY[i] * j);
            if (checkX < 0 || checkY < 0 || checkX > BOARD_SIZE || checkY > BOARD_SIZE)
                break ;

            
            if (game.getPos(checkX, checkY) != player)
                break ;
            else if (game.getPos(checkX, checkY) == player)
                ++(count[i / 2 % 2]);
        }
        if (i % 2 == 1){
            if (count[current] >= 5)
                return (true);
            count[current] = 1;
            (current == 0) ? current = 1 : current = 0;
        }
    }
    return (false);
}

bool checkDoubleThree(Board& copy, int y, int x, int dirY, int dirX, int center){
    int count = 1, empty = 0;
    int checkX = x, checkY = y;

    for (int j = 1; j < 5; j++) {
        checkX = x + (dirX * j);
        checkY = y + (dirY * j);
        if (checkX < 0 || checkY < 0 || checkX > BOARD_SIZE || checkY > BOARD_SIZE)
            break ;

        if (empty > 1 || (count == 3 && copy.isPosEmpty(checkX, checkY) == false))
            return false;
        else if (count == 3)
            break ;
        if (copy.getPos(checkX, checkY) == center)
            ++(count);
        else if (copy.getPos(checkX, checkY) == 0)
            ++empty;
        else
            break;
    }
    if (count == 3 && empty <= 1){
        return true;
    }
    return false;
}

//return true when there are a double three
bool    validGame(Board& copy, int yPoint, int xPoint, int player){
    const int   dirX[] = { 0, 0, 1, -1, 1, -1, 1, -1};
    const int   dirY[] = { 1, -1, 0, 0, 1, -1, -1, 1};
    
    int doubleThree = 0;
    
    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
            if (copy.isPosEmpty(x, y) == true)
                continue;
            doubleThree = 0;

            for (int i = 0; i < 8; i++){

                if (y == yPoint && x == xPoint && checkCapture(copy, y, x, dirY[i], dirX[i], player) == true){
                    copy.removePos(x + dirX[i], y + dirY[i]);
                    copy.removePos(x + (dirX[i] * 2), y + (dirY[i] * 2));
                }

                if (checkDoubleThree(copy, y, x, dirY[i], dirX[i], copy.getPos(x, y)) == true){
                    ++doubleThree;
                }

                if (doubleThree > 1){
                    return true;
                }
            }
        }
    }
    return false;
}

Heuristic minMaxRecursive(const Board &game, int init_player, int player, int depth, const int yGame, const int xGame, int alpha, int beta) {
    if (depth == 0 || checkWin(game, yGame, xGame, player) == true) {
        return (Heuristic (player, game, xGame, yGame));
    }

    // std::vector< std::future<cost> > threadResult;
    int value = (player == init_player) ? -2147483648 : 2147483647;
    // std::vector<Heuristic> result;
    bool cutoff = false;
    heuristicSet result;
    for (int y = 0; y < BOARD_SIZE && !cutoff; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (game.isPosEmpty(x, y) == false){
                std::cout << "Current player:" << game.getPos(x, y) << std::endl;
                auto res = game.extractPatterns(x, y, x + 4, y, player);
                if (!res.size())
                    continue;
                game.printBoard();
                std::cout << "Default extraction:" << res[Board::DEFAULT] << std::endl;
            }
            if (game.isPosEmpty(x, y) == true && emptyNeighbour(game, x, y) == false) {
                Board copy = game;
                copy.setPos(x, y, player);
                if (checkWin(copy, y, x, player) && depth == DEPTH){
                    // return Heuristic{INT_MAX, x, y};
                    Heuristic h = Heuristic(player, copy, x, y);
                    h.setHeuristic(INT_MAX);
                    return h;
                }

                if (validGame(copy, y, x, player) == true)
                    continue;
                int next_player = (player == BLACK) ? WHITE : BLACK;

                // std::cout << "Transpos extraction:" << res[Board::TRANSPOS] << std::endl;
                // if (depth == DEPTH)
                //     threadResult.push_back(async(std::launch::async, minMaxRecursive, copy, init_player, next_player, depth - 1, y, x, alpha, beta));
                // else{
                Heuristic recursiveResult = minMaxRecursive(copy, init_player, next_player, depth - 1, y, x, alpha, beta);
                result.insert(recursiveResult);
                if (player == init_player){
                    if (recursiveResult.getHeuristic() > value)
                        value = recursiveResult.getHeuristic();
                    if (value >= beta){
                        cutoff = true;
                        break ;
                    }
                    if (value > alpha)
                        alpha = value;
                }
                else {
                    if (recursiveResult.getHeuristic() < value)
                        value = recursiveResult.getHeuristic();
                    if (value <= alpha){
                        cutoff = true;
                        break ;
                    }
                    if (value < beta)
                        beta = value;
                }
                // }
            }
        }
    }
    
    // if (depth == DEPTH){
    //     int len = threadResult.size();
    //     for (int i = 0; i < len; i++){
    //         threadResult[i].wait();
    //     }
    //     for (int i = 0; i < len; i++){
    //         result.push_back(threadResult[i].get());
    //     }
    // }
    if (DEPTH == depth)
        std::cout << result.size() << "\n";
    if (init_player == player)
        return finCorrectValue(result, MAX);

    return finCorrectValue(result, MIN);;
}


void minMaxAlgorithm(Board &game, int &player, SDL_Renderer *renderer)
{
    int alpha = -2147483648, beta = 2147483647;

    // clock_t begin = clock();
    auto t_start = std::chrono::high_resolution_clock::now();
    Heuristic result =  minMaxRecursive(game, player, player, DEPTH, 0, 0, alpha, beta);
    const auto t_end = std::chrono::high_resolution_clock::now();
	// clock_t end = clock();
	// double timer = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    double timer = std::chrono::duration<double, std::milli>(t_end - t_start).count() / 1000;

    std::cout << "heuristic:" << result.getHeuristic() << " X: " << result.getX() << " Y: " << result.getY() <<"\n";
    {
        std::ostringstream message;

        message << std::fixed << std::setprecision(3) << timer;
        SDL_SetRenderDrawColor(renderer, 205, 127, 50, 255);

        SDL_Color textColor = {80, 0, 80, 255};
        SDL_Rect msg_rect = {SCREEN_WIDTH - MARGIN - OFFSET, SCREEN_HEIGHT - SCREEN_HEIGHT / 15, MARGIN + OFFSET, OFFSET};
        SDL_SetRenderDrawColor(renderer, 205, 127, 50, 255);
        SDL_RenderFillRect(renderer, &msg_rect);
        writeText(message.str(), "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", msg_rect, textColor, 24,renderer);
    }
    place_stone(game, player, renderer, result.getY(), result.getX());

}