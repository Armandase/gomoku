#include "../inc/minMaxAlgorithm.hpp"

void scoreUpdate(const int &playerCount, const int &opponentCount, int &score) {
    if (playerCount == 5) {
        score = INT_MAX;
        return ;
    }
    else if (playerCount == 4 && opponentCount == 0)
        score += 1000;
    else if (playerCount == 3 && opponentCount == 0)
        score += 100;
    else if (playerCount == 2 && opponentCount == 0)
        score += 10;
    else if (playerCount == 1 && opponentCount == 0)
        score += 1;
}

void scoreLine(const vector2d &game, int player, int x, int y, int &score) {
    int playerCount = 0;
    int opponentCount = 0;
    
    for (int k = 0; k < 5; ++k) {
        if (game[x][y + k] == player) {
            playerCount++;
        } else if (game[x][y + k] != 0) {
            opponentCount++;
        }
    }
    scoreUpdate(playerCount, opponentCount, score);
}

void scoreColumns(const vector2d &game, int player, int x, int y, int &score) {
    int playerCount = 0;
    int opponentCount = 0;
    
    for (int k = 0; k < 5; ++k) {
        if (game[x + k][y] == player) {
            playerCount++;
        } else if (game[x + k][y] != 0) {
            opponentCount++;
        }
    }
    scoreUpdate(playerCount, opponentCount, score);
}

int heuristic(const vector2d &game, int player) {
    int score = 0;
    for (int x = 0; x < BOARD_SIZE + 1; ++x) {
        for (int y = 0; y < BOARD_SIZE + 1; ++y) {
            if (y + 4 < BOARD_SIZE + 1) {
                scoreLine(game, player, x, y, score);
                if (score == INT_MAX)
                    return score;
            }
            if (x + 4 < BOARD_SIZE + 1) {
                scoreColumns(game, player, x, y, score);
                if (score == INT_MAX)
                    return score;
            }
        }
    }
    return score;
}

int minMaxRecursive(const vector2d &game, int init_player, int player, int depth) {
    if (depth == 0)
        // return heuristic(game, player);
        // h ?
        return 4;

    std::vector<int> result;
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (game[x][y] == 0) {
                vector2d copy = game;
                copy[x][y] = player;
                int next_player = (player == BLACK) ? WHITE : BLACK;
                result.push_back(minMaxRecursive(copy, init_player, next_player, depth - 1));
            }
        }
    }
    if (init_player == player) {
        auto it_max = std::max_element(result.begin(), result.end());
        return *it_max;
    }
    else {
        auto it_min = std::min_element(result.begin(), result.end());
        return *it_min;
    }
}
void minMaxAlgorithm(vector2d &game, int &player, SDL_Renderer *renderer)
{
    std::cout << minMaxRecursive(game, player, player, 2) << "\n";
}