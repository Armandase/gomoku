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

bool checkWin(const Heuristic& heuristic){
    const int   dirX[] = { 0, 0, 1, -1, 1, -1, 1, -1};
    const int   dirY[] = { 1, -1, 0, 0, 1, -1, -1, 1};
    int         checkX = 0, checkY = 0;
    int         count[2] = {1, 1};

    int current = 0;
    for (int i = 0; i < 8; i++){
        for (int j = 1; j < 5; j++){
            checkX = heuristic.getX() + (dirX[i] * j);
            checkY = heuristic.getY() + (dirY[i] * j);
            if (checkX < 0 || checkY < 0 || checkX > BOARD_SIZE || checkY > BOARD_SIZE)
                break ;

            
            if (heuristic.getGame().getPos(checkX, checkY) != heuristic.getPlayer())
                break ;
            else if (heuristic.getGame().getPos(checkX, checkY) == heuristic.getPlayer())
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

int getCurrentPlayer(int depth, int initPlayer){
    if (depth % 2 == DEPTH % 2)
        return initPlayer;
    return initPlayer == BLACK ? WHITE : BLACK;
}

Heuristic minMaxRecursive(Heuristic &heuristic, int initPlayer, int depth, int alpha, int beta) {
    if (depth == 0 || checkWin(heuristic) == true) {
        heuristic.globalHeuristic();
        return (heuristic);
        // return (Heuristic (player, game, xGame, yGame));
    }
    // std::vector< std::future<cost> > threadResult;
    int value = (initPlayer == heuristic.getPlayer()) ? -2147483648 : 2147483647;
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
            if (heuristic.getGame().isPosEmpty(x, y) == true && emptyNeighbour(heuristic.getGame(), x, y) == false) {
                Board copy = heuristic.getGame();
                copy.setPos(x, y, getCurrentPlayer(depth, initPlayer));
                if (validGame(copy, y, x, heuristic.getPlayer()) == false)
                    continue;
                if (checkWin(heuristic) == true){
                    Heuristic h = Heuristic(copy, x, y);
                    h.setHeuristic(INT_MAX);
                    return h;
                }

                // if (depth == DEPTH)
                //     threadResult.push_back(async(std::launch::async, minMaxRecursive, copy, init_player, next_player, depth - 1, y, x, alpha, beta));
                // else{
                Heuristic h = Heuristic(copy, x, y);
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
        if (getCurrentPlayer(depth, initPlayer) == initPlayer){
            auto it = result.begin();
            std::advance(it, i);    
            int next_player = (getCurrentPlayer(depth, initPlayer) == BLACK) ? WHITE : BLACK;
            Heuristic tmp = *it;
            recursiveResult.insert(minMaxRecursive(tmp, next_player, depth - 1, alpha, beta));
        }
        else{
            auto it = result.rbegin();
            std::advance(it, i);
            int next_player = (getCurrentPlayer(depth, initPlayer) == BLACK) ? WHITE : BLACK;
            Heuristic tmp = *it;
            recursiveResult.insert(minMaxRecursive(tmp, next_player, depth - 1, alpha, beta));
        } 

    }

    if (initPlayer == getCurrentPlayer(depth, initPlayer))
        return finCorrectValue(recursiveResult, MAX);

    return finCorrectValue(recursiveResult, MIN);
}

heuristicSet generatePossibleMoves(Board& game, int player){
    heuristicSet possibleMoves;
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (game.isPosEmpty(x, y) == true && emptyNeighbour(game, x, y) == false) {
                Board copy = game;
                copy.setPos(x, y, getCurrentPlayer(DEPTH, player));
                if (validGame(copy, y, x, player) == false)
                    continue;

                Heuristic h = Heuristic(copy, x, y);
                if (checkWin(h) == true){
                    h.setHeuristic(INT_MAX);
                    possibleMoves.insert(h);
                    return possibleMoves;
                }
                h.setHeuristic(h.localHeuristic(x, y));
                possibleMoves.insert(h);
            }
        }
    }
    return possibleMoves;
}

int indexOfMaxValue(const std::vector<Heuristic>& vec){
    int max = INT32_MIN;
    int idx = -1;
    int size = vec.size();

    for (int i = 0; i < size; i++){
        if (vec[i].getHeuristic() > max)
        {
            max = vec[i].getHeuristic();
            idx = i;
        }
    }
    if (idx == -1)
        throw std::runtime_error((std::string(__FUNCTION__ ) + std::string(": not found")));

    return idx;
}

Heuristic    minMaxFirstStep(Board& game, int player){
    heuristicSet possibleMoves = generatePossibleMoves(game, player);
    std::vector<std::future<Heuristic>> threadResult;

    int alpha = -2147483648, beta = 2147483647;

    int limit = (PRUNING < possibleMoves.size()) ? PRUNING : possibleMoves.size();
    for (int i = 0; i < limit; i ++){
        auto it = possibleMoves.begin();
        std::advance(it, i);    
        int next_player = (player == BLACK) ? WHITE : BLACK;
        Heuristic tmp = *it;
        threadResult.push_back(std::async(std::launch::async, minMaxRecursive, std::ref(tmp), next_player, DEPTH - 1, alpha, beta));
    }

    std::vector<Heuristic> recursiveResult;
    for (int i = 0; i < threadResult.size(); i ++){
        threadResult[i].wait();
        if (threadResult[i].valid() == true){
            Heuristic threadReturn = threadResult[i].get();
            recursiveResult.push_back(threadReturn);
        } else {
            std::cerr << "Fail to join a future" << std::endl; 
        }
    }
    int idx =  indexOfMaxValue(recursiveResult);

    auto finalIt = possibleMoves.begin();   
    std::advance(finalIt, idx);
    return *finalIt;
}

void    minMaxAlgorithm(Board &game, int &player, Render& render)
{

    try {
    auto t_start = std::chrono::high_resolution_clock::now();
    Heuristic result =  minMaxFirstStep(game, player);
    const auto t_end = std::chrono::high_resolution_clock::now();
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