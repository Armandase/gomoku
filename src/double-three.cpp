#include "../inc/gomoku.hpp"
#include "../inc/Board.hpp"

int width = {BOARD_SIZE + 1};

int count_in_direction(Board::bitboard& playerBoard, Board::bitboard& enemyBoard, int startRow, int startCol, int rowDelta, int colDelta) {
    int count = 0;
    
    // Continue moving in the specified direction
    for (int d = 1; d < 4; d++) {  // Check up to 3 pieces in the direction
        int newRow = startRow + d * rowDelta;
        int newCol = startCol + d * colDelta;
        
        // Check boundaries and enemy pieces

        if (newRow < 0 || newRow >= width || newCol < 0 || newCol >= width)
            break;
        if (enemyBoard[newRow * width + newCol])
            return -1;
        
        // Count player's pieces
        if (playerBoard[newRow * width + newCol])
            count++;
    }
    
    return count;
}

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

bool check_double_free_three(Board::bitboard& playerBoard, Board::bitboard& enemyBoard, int col, int row) {
    const int   dirX[] = { 0, 0, 1, -1, 1, -1, 1, -1};
    const int   dirY[] = { 1, -1, 0, 0, 1, -1, -1, 1};
    int count;
    int double_three = 0;

    Board::bitboard newBoard = playerBoard;
    newBoard.set(col + row * width);
    printB(newBoard, enemyBoard, col, row);
    for (int i = 0; i < 8; i += 2){
        count = 1;
        int dirA = count_in_direction(newBoard, enemyBoard, row, col, dirX[i], dirY[i]); 
        int dirB = count_in_direction(newBoard, enemyBoard, row, col, dirX[i + 1], dirY[i + 1]);
        if (dirA >= 2 && dirB >= 2)
            return true;
        count += dirA + dirB;
        if (count >= 3)
            double_three++;
    }

    return double_three >= 2;
}