#include "../inc/Board.hpp"

TEST(Board_extractPatterns, TestInputExtraction){
    Board::bitboard test(
"0111110000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000");

    Board::bitboard waited_result(
"0000000000000000000"
"1000000000000000000"
"1000000000000000000"
"1000000000000000000"
"1000000000000000000"
"1000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000"
"0000000000000000000");

    Board gameTest;
    int player = 0;
    for (int i = 0; i < test.size(); i++){
        if (!test[i])
            continue;
        std::cout << "Pos to place x:" << i % gameTest.getWidth() << " y: " << i / gameTest.getWidth() << std::endl;
        gameTest.setPos(i % gameTest.getWidth(), i / gameTest.getWidth(), test[i]);
    }
    
    Board::patternMap waitedResult;
    patternBitset pattern("1011");
    waitedResult.insert(Board::patternPair(Board::PatternType::DEFAULT,pattern));
    waitedResult.insert(Board::patternPair(Board::PatternType::TRANSPOS, pattern));
    waitedResult.insert(Board::patternPair(Board::PatternType::DIAG, pattern));
    waitedResult.insert(Board::patternPair(Board::PatternType::ANTIDIAG, pattern));

    EXPECT_EQ(gameTest.extractPatterns(19-7, 19-7, 5, 1), waitedResult);
}

// TEST(Board_extractPatterns, TestInputExtraction){
//     Board::bitboard test(
// "0000000000000000000"
// "0000000000000000000"
// "0000000000000000000"
// "0001001000000000000"
// "0000000000000000000"
// "0000011000000000000"
// "0001011000000000000"
// "0000011000000000000"
// "0000000000000000000"
// "0001001000000000000"
// "0000000000000000000"
// "0000000000000000000"
// "0000000000000000000"
// "0000000000000000000"
// "0000000000000000000"
// "0000000000000000000"
// "0000000000000000000"
// "0000000000000000000"
// "0000000000000000000");

//     Board gameTest;
//     int player = 0;
//     for (int i = 0; i < test.size(); i++){
//         if (!test[i])
//             continue;
//         std::cout << "Pos to place x:" << i % gameTest.getWidth() << " y: " << i / gameTest.getWidth() << std::endl;
//         gameTest.setPos(i % gameTest.getWidth(), i / gameTest.getWidth(), test[i]);
//     }
    
//     Board::patternMap waitedResult;
//     patternBitset pattern("1011");
//     waitedResult.insert(Board::patternPair(Board::PatternType::DEFAULT,pattern));
//     waitedResult.insert(Board::patternPair(Board::PatternType::TRANSPOS, pattern));
//     waitedResult.insert(Board::patternPair(Board::PatternType::DIAG, pattern));
//     waitedResult.insert(Board::patternPair(Board::PatternType::ANTIDIAG, pattern));

//     EXPECT_EQ(gameTest.extractPatterns(19-7, 19-7, 5, 1), waitedResult);
// }