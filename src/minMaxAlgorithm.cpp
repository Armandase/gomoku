#include "../inc/minMaxAlgorithm.hpp"
#include "../inc/utils.hpp"
// #include "../inc/Pattern.hpp"

Heuristic finCorrectValue(const heuristicSet& recursiveResult, int minOrMax){
    if (recursiveResult.empty())
        throw std::runtime_error("Empty vector of recursive\n");
    if (minOrMax == MAX){
        return *recursiveResult.rbegin();
    }
    return *recursiveResult.begin();
}

Heuristic minMaxRecursive(Heuristic &heuristic, int initPlayer, int depth, int alpha, int beta) {
    if (depth == 0 || checkWin(heuristic) == true) {
        heuristic.setHeuristic(heuristic.globalHeuristic());
        return (heuristic);
    }
    // int value = (initPlayer == heuristic.getPlayer()) ? -2147483648 : 2147483647;
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
            // if (heuristic.getGame().isPosEmpty(x, y) == true ) {
            if (heuristic.getGame().isPosEmpty(x, y) == true && emptyNeighbour(heuristic.getGame(), x, y) == false) {
                Board copy = heuristic.getGame();
                copy.setPos(x, y, getCurrentPlayer(depth, initPlayer));
                if (validGame(copy, y, x, heuristic.getPlayer()) == false)
                    continue;
                if (checkWin(heuristic) == true){
                    Heuristic h(copy, x, y, heuristic.getBeginX(), heuristic.getBeginY());
                    h.setHeuristic(INT_MAX);
                    return h;
                }

                Heuristic h(copy, x, y, heuristic.getBeginX(), heuristic.getBeginY());
                h.setHeuristic(h.localHeuristic(x, y));
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
        //takes the max values
        if (getCurrentPlayer(depth, initPlayer) == initPlayer){
            auto it = result.begin();
            std::advance(it, i);    
            Heuristic tmp = *it;
            recursiveResult.insert(minMaxRecursive(tmp, initPlayer, depth - 1, alpha, beta));
        }
        else{
            auto it = result.rbegin();
            std::advance(it, i);
            Heuristic tmp = *it;
            recursiveResult.insert(minMaxRecursive(tmp, initPlayer, depth - 1, alpha, beta));
        } 
    }
    
    if (initPlayer == getCurrentPlayer(depth, initPlayer))
        return finCorrectValue(recursiveResult, MAX);

    return finCorrectValue(recursiveResult, MIN);
}


Heuristic    minMaxFirstStep(Board& game, int player){
    std::vector<std::future<Heuristic> > threadResult;
    
    {
        heuristicSet possibleMoves = generatePossibleMoves(game, player);

        int alpha = -2147483648, beta = 2147483647;

        int limit = (PRUNING < possibleMoves.size()) ? PRUNING : possibleMoves.size();
        for (int i = 0; i < limit; i ++){
            auto it = possibleMoves.begin();
            std::advance(it, i);
            Heuristic tmp = *it;
            threadResult.push_back(std::async(std::launch::async, minMaxRecursive, std::ref(tmp), player, DEPTH , alpha, beta));
        }
    }

    heuristicSet recursiveResult;
    int size = threadResult.size();
    for (int i = 0; i < size; i ++){
        threadResult[i].wait();
        if (threadResult[i].valid() == true){
            Heuristic threadReturn = threadResult[i].get();
            recursiveResult.insert(threadReturn);
        } else {
            std::cerr << "Fail to join a future" << std::endl; 
        }
    }
    Heuristic result = *recursiveResult.begin();
    return result;
}

// void    minMaxAlgorithm(Board &game, int &player, Render& render)
// {

//     try {
//     auto t_start = std::chrono::high_resolution_clock::now();
//     Heuristic result =  minMaxFirstStep(game, player);
//     const auto t_end = std::chrono::high_resolution_clock::now();
//     double timer = std::chrono::duration<double, std::milli>(t_end - t_start).count() / 1000;
//     std::cout << "heuristic:" << result.getHeuristic() << " X: " << result.getBeginX() << " Y: " << result.getBeginY() <<"\n";
//     {
//         std::ostringstream message;

//         message << std::fixed << std::setprecision(3) << timer;
//         SDL_SetRenderDrawColor(render.getRenderer(), 205, 127, 50, 255);

//         SDL_Color textColor = {80, 0, 80, 255};
//         SDL_Rect msg_rect = {SCREEN_WIDTH - MARGIN - OFFSET, SCREEN_HEIGHT - SCREEN_HEIGHT / 15, MARGIN + OFFSET, OFFSET};
//         SDL_SetRenderDrawColor(render.getRenderer(), 205, 127, 50, 255);
//         SDL_RenderFillRect(render.getRenderer(), &msg_rect);
//         render.writeText(message.str(), "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", msg_rect, textColor, 24);
//     }
//     place_stone(game, player, render, result.getBeginY(), result.getBeginX());
//     } catch (std::exception& e){
//         std::cout << e.what() << std::endl;
//     }

// }