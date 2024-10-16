#include "../inc/Game.hpp"
#include "../inc/ClassicBoard.hpp"
#include <gtest/gtest.h>

TEST(IBoard, TestTransposedBoard){
    IBoard::bitboard test(
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

    IBoard::bitboard waited_result(
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

    Game gameTest;
    int player = 0;
    int width = gameTest.getClassicBoard().getWidth();
    for (int i = 0; i < test.size(); i++){
        if (!test[i])
            continue;
        gameTest.setPosToBoards(i % width, i / width, test[i]);
    }
    
    EXPECT_EQ(gameTest.getTransposedBoard().getPlayer1(), waited_result);
}


TEST(IBoard, TestDiagBoard){
    IBoard::bitboard test(
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

    IBoard::bitboard waited_result(
"0000000000000000000"
"0100000000000000000"
"0010000000000000000"
"0001000000000000000"
"0000100000000000000"
"0000010000000000000"
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

    Game gameTest;
    int player = 0;
    int width = gameTest.getDiagBoard().getWidth();
    for (int i = 0; i < test.size(); i++){
        if (!test[i])
            continue;
        gameTest.setPosToBoards(i % width, i / width, test[i]);
    }
    
    gameTest.getClassicBoard().printBoard();
    gameTest.getDiagBoard().printBoard();

    EXPECT_EQ(gameTest.getDiagBoard().getPlayer1(), waited_result);
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

// Custom listener that triggers on failure of specific tests
class FailListener : public ::testing::TestEventListener {
 public:
  // Override the method to check for test results
  void OnTestPartResult(const ::testing::TestPartResult& result) override {
    if (result.failed()) {
      const ::testing::TestInfo* test_info =
          ::testing::UnitTest::GetInstance()->current_test_info();
      if (test_info != nullptr) {
        std::string test_name = std::string(test_info->test_suite_name()) + "." + test_info->name();
        
        // Specify the test you want to call the custom function for
        if (test_name == "IBoard.TestTransposedBoard") {
          OnTestFailure();
        }
      }
    }
  }

  void OnTestFailure() {

  }
};

