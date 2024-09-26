#ifndef __PATTERN_HPP__
#define __PATTERN_HPP__

# include "gomoku.hpp"
# include <vector>
# include "Board.hpp"

class Board;

class Pattern{
    public:


    public:
        static patternsVector getPatterns(){
            return (Pattern()._patterns);
        }

        static void compareBoardsWithPattern(Board& gameBoard, int xPos, int yPos)
        {
            patternBitset defaultPattern;
            patternBitset transposPattern;
            patternBitset diagPattern;
            patternBitset antiDiagPattern;

            for (auto& pattern: Pattern::getPatterns()){
                // gameBoard
                std::cout << "Pattern for " << xPos << " : " << yPos << std::endl;
                // std::cout << "Found pattern:" << gameBoard.extractPatterns(xPos, yPos, xPos + PARTTERN_SIZE, yPos + PARTTERN_SIZE, 1) << std::endl;
                exit(1);

                // pattern.to_ullong()

                // pattern.to_ullong() != r.to_ulong();
            }
        }

        static void matchPatternBoard(Board& gameBoard){
            
            for (int y = 0; y < BOARD_SIZE; y++) {
                for (int x = 0; x < BOARD_SIZE; x++) {
                    if (gameBoard.isPosEmpty(x, y) == true)
                        continue ;
                    Pattern::compareBoardsWithPattern(gameBoard, x, y);
                }
            }
        }

    private:
        const patternsVector _patterns = {
            patternBitset("1001"),
            patternBitset("1100"),
            patternBitset("0011"),
            patternBitset("1010"),
            patternBitset("0101"),
            patternBitset("1111"),
            patternBitset("1101"),
            patternBitset("1011")
        };
};

#endif
