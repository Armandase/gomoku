#ifndef __PATTERN_HPP__
#define __PATTERN_HPP__

# include "gomoku.hpp"
# include <vector>
# include "Board.hpp"

class Board;

class Pattern{
    public:
        static patternsVector getPatterns(){
            return (Pattern()._patterns);
        }

        static bool compareBoardsWithPattern(Board::patternMap patterns)
        {
            ulong defaultPattern = patterns[Board::DEFAULT].to_ulong();
            ulong transposPattern = patterns[Board::TRANSPOS].to_ulong();
            ulong diagPattern = patterns[Board::DIAG].to_ulong();
            ulong antiDiagPattern = patterns[Board::ANTIDIAG].to_ulong();

            for (auto& pattern: Pattern::getPatterns()){
                if (pattern.to_ullong() == defaultPattern 
                ||  pattern.to_ullong() == defaultPattern
                ||  pattern.to_ullong() == defaultPattern
                ||  pattern.to_ullong() == defaultPattern)
                return true;
            }
            return false;
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
