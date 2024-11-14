// #ifndef __PATTERN_HPP__
// #define __PATTERN_HPP__

// # include "gomoku.hpp"
// # include "Game.hpp"
// # include <vector>

// class Pattern{
//     public:

//         static patternMap getPatterns(){
//             return (Pattern()._patterns);
//         }

//         static patternMap getCapturePatterns(){
//             return (Pattern()._capturePattern);
//         }

//         static bool compareBoardsWithPattern(Game::patternMap patterns)
//         {
//             ulong defaultPattern = patterns[Game::CLASSIC].to_ulong();
//             ulong transposPattern = patterns[Game::TRANSPOS].to_ulong();
//             ulong diagPattern = patterns[Game::DIAG].to_ulong();
//             ulong antiDiagPattern = patterns[Game::ANTIDIAG].to_ulong();

//             for (auto& pattern: Pattern::getPatterns()){
//                 if (pattern.to_ulong() == defaultPattern
//                 ||  pattern.to_ulong() == transposPattern
//                 ||  pattern.to_ulong() == diagPattern
//                 ||  pattern.to_ulong() == antiDiagPattern)
//                 return true;
//             }
//             return false;
//         }
//     private:
//         const heuristicMap _patterns = {
//             patternBitset("1001"),
//             patternBitset("1100"),
//             patternBitset("0011"),
//             patternBitset("1010"),
//             patternBitset("0101"),
//             patternBitset("1111"),
//             patternBitset("1101"),
//             patternBitset("1011")
//         };

//          const patternBitset _capturePattern = patternBitset("1001");
// };

// #endif
