#include "../inc/minMaxAlgorithm.hpp"
#include "../inc/utils.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <future>
# include <set>
#include "../inc/Pattern.hpp"


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
    if (minOrMax == MAX){
        return *recursiveResult.rbegin();
    }
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

// bool checkDoubleThree(Board& copy, int y, int x, int dirY, int dirX, int center){
//     int count = 1, empty = 0;
//     int checkX = x, checkY = y;

//     for (int j = 1; j < 5; j++) {
//         checkX = x + (dirX * j);
//         checkY = y + (dirY * j);
//         if (checkX < 0 || checkY < 0 || checkX > BOARD_SIZE || checkY > BOARD_SIZE)
//             break ;

//         if (empty > 1 || (count == 3 && copy.isPosEmpty(checkX, checkY) == false))
//             return false;
//         else if (count == 3)
//             break ;
//         if (copy.getPos(checkX, checkY) == center)
//             ++(count);
//         else if (copy.getPos(checkX, checkY) == 0)
//             ++empty;
//         else
//             break;
//     }
//     if (count == 3 && empty <= 1){
//         return true;
//     }
//     return false;
// }

//return false when there are a double three
bool    validGame(Board& copy, int yPoint, int xPoint, int player){
    const int   dirX[] = { 0, 0, 1, -1, 1, -1, 1, -1};
    const int   dirY[] = { 1, -1, 0, 0, 1, -1, -1, 1};
    
    if (copy.checkDoubleThree(xPoint, yPoint, player))
        return true;
        
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
            }
        }
    }
    return true;
}

Heuristic minMaxRecursive(const Board &game, int init_player, int player, int depth, const int yGame, const int xGame, int alpha, int beta) {
    if (depth == 0 || checkWin(game, yGame, xGame, player) == true) {
        return (Heuristic (player, game, xGame, yGame));
    }
    // std::vector< std::future<cost> > threadResult;
    int value = (player == init_player) ? -2147483648 : 2147483647;
    bool cutoff = false;
    heuristicSet result;
    for (int y = 0; y < BOARD_SIZE && !cutoff; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            // if (game.isPosEmpty(x, y) == false){
            //     Board::patternMap multiDirectionnalPatterns = game.extractPatterns(x, y, 4, player);
            //     if (!multiDirectionnalPatterns.size())
            //         continue;
            //     bool found = Pattern::compareBoardsWithPattern(multiDirectionnalPatterns);
            //     if (found == false)
            //         continue;
            // }
            if (game.isPosEmpty(x, y) == true && emptyNeighbour(game, x, y) == false) {
                Board copy = game;
                copy.setPos(x, y, player);
                if (validGame(copy, y, x, player) == false)
                    continue;
                if (checkWin(copy, y, x, player) == true){
                    Heuristic h = Heuristic(player, copy, x, y);
                    h.setHeuristic(INT_MAX);
                    return h;
                }

                int next_player = (player == BLACK) ? WHITE : BLACK;

                // if (depth == DEPTH)
                //     threadResult.push_back(async(std::launch::async, minMaxRecursive, copy, init_player, next_player, depth - 1, y, x, alpha, beta));
                // else{
                Heuristic h = Heuristic(player, copy, x, y);
                h.setHeuristic(h.localHeuristic(x, y));
                // Heuristic recursiveResult = minMaxRecursive(copy, init_player, next_player, depth - 1, y, x, alpha, beta);
                result.insert(h);
                // if (player == init_player){
                //     if (recursiveResult.getHeuristic() > value)
                //         value = recursiveResult.getHeuristic();
                //     if (value >= beta || result.begin()->getHeuristic() == 2147483647){
                //         cutoff = true;
                //         break ;
                //     }
                //     if (value > alpha)
                //         alpha = value;
                // }
                // else {
                //     if (recursiveResult.getHeuristic() < value)
                //         value = recursiveResult.getHeuristic();
                //     if (value <= alpha || long(result.rbegin()->getHeuristic()) == -21474836478){
                //         cutoff = true;
                //         break ;
                //     }
                //     if (value < beta)
                //         beta = value;
                // }
                // }
            }
        }
    }

    heuristicSet recursiveResult;
    int limit = (PRUNING < result.size()) ? PRUNING : result.size();
    for (int i = 0; i < limit; i ++){
        if (init_player == player){
            auto it = result.begin();
            std::advance(it, i);    
            int next_player = (it->getPlayer() == BLACK) ? WHITE : BLACK;
            recursiveResult.insert(minMaxRecursive(it->getGame(), init_player, next_player, depth - 1, it->getY(), it->getX(), alpha, beta));
        }
        else{
            auto it = result.rbegin();
            std::advance(it, i);
            int next_player = (it->getPlayer() == BLACK) ? WHITE : BLACK;
            recursiveResult.insert(minMaxRecursive(it->getGame(), init_player, next_player, depth - 1, it->getY(), it->getX(), alpha, beta));
        } 

    }

    if (init_player == player)
        return finCorrectValue(recursiveResult, MAX);

    return finCorrectValue(recursiveResult, MIN);
}


void minMaxAlgorithm(Board &game, int &player, Render& render)
{
    int alpha = -2147483648, beta = 2147483647;

    // clock_t begin = clock();
    try {
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
        SDL_SetRenderDrawColor(render.getRenderer(), 205, 127, 50, 255);

        SDL_Color textColor = {80, 0, 80, 255};
        SDL_Rect msg_rect = {SCREEN_WIDTH - MARGIN - OFFSET, SCREEN_HEIGHT - SCREEN_HEIGHT / 15, MARGIN + OFFSET, OFFSET};
        SDL_SetRenderDrawColor(render.getRenderer(), 205, 127, 50, 255);
        SDL_RenderFillRect(render.getRenderer(), &msg_rect);
        render.writeText(message.str(), "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", msg_rect, textColor, 24);
    }
    place_stone(game, player, render, result.getY(), result.getX());
    } catch (std::exception& e){
        (void)e;
    }

}