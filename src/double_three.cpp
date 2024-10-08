#include "../inc/gomoku.hpp"
#include "../inc/Board.hpp"

int width = {BOARD_SIZE + 1};



void printB(Board::bitboard& playerBoard, Board::bitboard& enemyBoard, int testCol, int testRow) {
    for (int r = 0; r < width; r++) {
        for (int c = 0; c < width; c++) {
            if (r == testRow && c == testCol) {
                std::cout << "X "; // TEST POS
            } else if (playerBoard[r * width + c]) {
                std::cout << "W "; // White
            } else if (enemyBoard[r * width + c]) {
                std::cout << "B "; // Black
            } else {
                std::cout << ". "; // Empty
            }
        }
        std::cout << std::endl;
    }
}
