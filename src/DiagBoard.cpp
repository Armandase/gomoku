#include "../inc/DiagBoard.hpp"
#include "../inc/Pattern.hpp"

DiagBoard::DiagBoard():
    IBoard()
{
    resetBoard();
}

DiagBoard::~DiagBoard(){

};

DiagBoard::DiagBoard(const DiagBoard &cpy):
    IBoard::IBoard(cpy)
{
}

DiagBoard &DiagBoard::operator=(const DiagBoard &rhs)
{
    if (this != &rhs)
    {
	    IBoard::operator=(rhs);
    }
    return (*this);
}

uint16_t  DiagBoard::convertCoordinate(uint16_t x, uint16_t y) const noexcept
{
    int newY = (x + y) % IBoard::getWidth();
    return (x + newY * IBoard::getWidth());
};

patternBitset DiagBoard::extractPattern(uint16_t xPos, uint16_t yPos, uint16_t length, int player) const{
    int xEnd = xPos + length % IBoard::getWidth();
    int yEnd = yPos + (length / IBoard::getWidth());

    if (IBoard::isValidPos(xEnd, yEnd) == false || (xPos < yEnd + 1 && xEnd > yEnd + 1))
        return patternBitset(0);
    
    int convertedCoordinate = this->convertCoordinate(xPos, yPos);

    bitboard mask("1111");
    bitboard extractedPattern(0);
    if (player == IBoard::getIdPlayer1())
        extractedPattern = IBoard::getPlayer1() &  (mask << convertedCoordinate);
    else
        extractedPattern = IBoard::getPlayer2() &  (mask << convertedCoordinate);
    extractedPattern >>= convertedCoordinate;
    return patternBitset(extractedPattern.to_ulong());
}

// IBoard::patternMap DiagBoard::extractPatterns(unsigned int xPos, unsigned int yPos, unsigned int length, int player) const{
//     patternMap result{};
//     bool handleDiag = true;
//     bool handleAntiDiag = true;

//     int xEnd = xPos + length % this->_width;
//     int yEnd = yPos + (length / this->_width);
    
//     if (xEnd > this->_width || yEnd > this->_width){
//         return result;
//     }
//     if (xPos <= yEnd + 1 && xEnd >= yEnd + 1)
//         handleDiag = false;
//     if (this->_width - xPos <= yEnd - 1 && this->_width - xEnd >= yEnd - 1)
//         handleAntiDiag = false;
    

//     int beginDefault = xPos + yPos * this->_width;
//     int beginTranspose = this->coordinateToTranspose1D(xPos, yPos);
//     int beginDiag = this->coordinateToDiag1D(xPos, yPos);
//     int beginAntiDiag = this->coordinateToAntiDiag1D(xPos, yPos);

//     patternBitset defaultBitset(0);
//     patternBitset transposBitset(0);
//     patternBitset diagBitset(0);
//     patternBitset antiDiagBitset(0);
//     for (int i = 0; i < length; ++i) {
//         if (player == this->_idPlayer1){
//             defaultBitset[i] = _player1[beginDefault + i];
//             transposBitset[i] = _player1Transposed[beginTranspose + i];
//             if (handleDiag)
//                 diagBitset[i] = _player1Diag[beginDiag + i];
//             if (handleAntiDiag)
//                 antiDiagBitset[i] = _player1AntiDiag[beginAntiDiag + i];
//         } else {
//             defaultBitset[i] = _player2[beginDefault + i];
//             transposBitset[i] = _player2Transposed[beginTranspose + i];
//             if (handleDiag)
//                 diagBitset[i] = _player1Diag[beginDiag + i];
//             if (handleAntiDiag)
//                 antiDiagBitset[i] = _player1AntiDiag[beginAntiDiag + i];
//         }
//     }
//     result.insert(patternPair(IBoard::PatternType::DEFAULT, defaultBitset));
//     result.insert(patternPair(IBoard::PatternType::TRANSPOS, transposBitset));
//     result.insert(patternPair(IBoard::PatternType::DIAG, diagBitset));
//     result.insert(patternPair(IBoard::PatternType::ANTIDIAG, antiDiagBitset));

//     return result;
// }

// IBoard::patternBitset DiagBoard::extractPattern(uint16 xPos, uint16 yPos, uint16 length, int player) const{
//     int xEnd = xPos + length % this->_width;
//     int yEnd = yPos + (length / this->_width);

//     if (this->isPosValid(xEnd, yEnd) == false)
//         return nullptr;

//     // if (xPos <= yEnd + 1 && xEnd >= yEnd + 1)
//     //     handleDiag = false;
//     // if (this->_width - xPos <= yEnd - 1 && this->_width - xEnd >= yEnd - 1)
//     //     handleAntiDiag = false;
    
//     int convertedCoordinate = this->convertCoordinate(x, y);

//     patternBitset result(0);

//     bitboard mask(15);
//     bitboard extractedPattern(0);
//     if (player == this->_idPlayer1)
//         extractedPattern = this->_player1 &  (mask << convertedCoordinate);
//     else
//         extractedPattern = this->_player2 &  (mask << convertedCoordinate);
        
//     return patternBitset(pattern.to_ulong());
// }

// IBoard::patternMap DiagBoard::extractPatternsReversed(unsigned int xPos, unsigned int yPos, unsigned int length, int player) const{
//     patternMap result{};
//     bool handleDiag = true;
//     bool handleAntiDiag = true;

//     int xEnd = xPos - length % this->_width;
//     int yEnd = yPos - (length / this->_width);
    
//     if (xEnd > this->_width || yEnd > this->_width){
//         return result;
//     }
//     if (xPos <= yEnd + 1 && xEnd >= yEnd + 1)
//         handleDiag = false;
//     if (this->_width - xPos <= yEnd - 1 && this->_width - xEnd >= yEnd - 1)
//         handleAntiDiag = false;
    

//     int beginDefault = xPos + yPos * this->_width;
//     int beginTranspose = this->coordinateToTranspose1D(xPos, yPos);
//     int beginDiag = this->coordinateToDiag1D(xPos, yPos);
//     int beginAntiDiag = this->coordinateToAntiDiag1D(xPos, yPos);

//     patternBitset defaultBitset(0);
//     patternBitset transposBitset(0);
//     patternBitset diagBitset(0);
//     patternBitset antiDiagBitset(0);
//     for (int i = 0; i < length; ++i) {
//         if (player == this->_idPlayer1){
//             defaultBitset[i] = _player1[beginDefault - i];
//             transposBitset[i] = _player1Transposed[beginTranspose - i];
//             if (handleDiag)
//                 diagBitset[i] = _player1Diag[beginDiag - i];
//             if (handleAntiDiag)
//                 antiDiagBitset[i] = _player1AntiDiag[beginAntiDiag - i];
//         } else {
//             defaultBitset[i] = _player2[beginDefault - i];
//             transposBitset[i] = _player2Transposed[beginTranspose - i];
//             if (handleDiag)
//                 diagBitset[i] = _player1Diag[beginDiag - i];
//             if (handleAntiDiag)
//                 antiDiagBitset[i] = _player1AntiDiag[beginAntiDiag - i];
//         }
//     }
//     result.insert(patternPair(IBoard::PatternType::REV_DEFAULT, defaultBitset));
//     result.insert(patternPair(IBoard::PatternType::REV_TRANSPOS, transposBitset));
//     result.insert(patternPair(IBoard::PatternType::REV_DIAG, diagBitset));
//     result.insert(patternPair(IBoard::PatternType::REV_ANTIDIAG, antiDiagBitset));

//     return result;
// }