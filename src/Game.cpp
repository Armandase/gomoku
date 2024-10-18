#include "../inc/Game.hpp"
#include "../inc/IBoard.hpp"

Game::Game():
    _classicBoard(),
    _transposedBoard(),
    _antiDiagBoard(),
    _diagBoard(),
    _player1Capture(0),
    _player2Capture(0)
{
}

Game::~Game()
{
}

Game::Game(const Game &cpy):
    _classicBoard(cpy._classicBoard),
    _transposedBoard(cpy._transposedBoard),
    _antiDiagBoard(cpy._antiDiagBoard),
    _diagBoard(cpy._diagBoard),
    _player1Capture(cpy._player1Capture),
    _player2Capture(cpy._player2Capture)
{
}

Game &Game::operator=(const Game &rhs)
{
    if (this != &rhs)
    {
        this->_classicBoard = rhs._classicBoard;
        this->_transposedBoard = rhs._transposedBoard;
        this->_antiDiagBoard = rhs._antiDiagBoard;
        this->_diagBoard = rhs._diagBoard;
        this->_player1Capture = rhs._player1Capture;
        this->_player2Capture = rhs._player2Capture;
    }
    return (*this);
}

uint16_t Game::getCapture(int player) {
    if (player == this->getClassicBoard().getIdPlayer1())
        return _player1Capture;
    else if (player == this->getClassicBoard().getIdPlayer2())
        return _player2Capture;
    return 0;
}

void Game::addCapture(int player) {
    if (player == this->getClassicBoard().getIdPlayer1())
        _player1Capture++;
    else if (player == this->getClassicBoard().getIdPlayer2())
        _player2Capture++;
}

ClassicBoard& Game::getClassicBoard() noexcept{
    return(this->_classicBoard);
}

TransposedBoard& Game::getTransposedBoard() noexcept{
    return(this->_transposedBoard);
}

AntiDiagBoard& Game::getAntiDiagBoard() noexcept{
    return(this->_antiDiagBoard);
}

DiagBoard& Game::getDiagBoard() noexcept{
    return((this->_diagBoard));
}

void    Game::setPosToBoards(uint16_t x, uint16_t y, int player){
    _classicBoard.setPos(x, y, player);
    _transposedBoard.setPos(x, y, player);
    _antiDiagBoard.setPos(x, y, player);
    _diagBoard.setPos(x, y, player);
}

void    Game::removePosToBoards(uint16_t x, uint16_t y){
    _classicBoard.removePos(x, y);
    _transposedBoard.removePos(x, y);
    _antiDiagBoard.removePos(x, y);
    _diagBoard.removePos(x, y);
}

void    Game::resetBoards(){
    _classicBoard.resetBoard();
    _transposedBoard.resetBoard();
    _antiDiagBoard.resetBoard();
    _diagBoard.resetBoard();
}

bool Game::checkPossibleCapture(uint16_t x, uint16_t y, Game::PatternType boardType, uint16_t player) {
    const int   opponent = (player == WHITE) ? BLACK : WHITE;
    const int   dirX[8] = {1, 0, 1, 1, -1, 0, -1, -1};
    const int   dirY[8] = {0, 1, -1, 1, 0, -1, 1, -1};
    for (int i = 0; i < 5; i++) {
        x = x + dirX[boardType];
        y = y + dirY[boardType];

        for (int j = 0; j < 4; j++) {
            if (getClassicBoard().isValidPos(x + dirX[j + 4], y + dirY[j + 4])
            && getClassicBoard().isValidPos(x + dirX[j] * 2, y + dirY[j] * 2)) {
                if (getClassicBoard().getPos(x + dirX[j + 4], y + dirY[j + 4]) == opponent
                && getClassicBoard().getPos(x + dirX[j], y + dirY[j]) == player
                && getClassicBoard().getPos(x + dirX[j] * 2, y + dirY[j] * 2) == 0)
                    return true;

                if (getClassicBoard().getPos(x + dirX[j + 4], y + dirY[j + 4]) == 0 
                && getClassicBoard().getPos(x + dirX[j], y + dirY[j]) == player 
                && getClassicBoard().getPos(x + dirX[j] * 2, y + dirY[j] * 2) == opponent)
                    return true;
            }
        }
    }
    return false;
}

bool Game::playerWin(uint16_t player){
    if (getCapture(player) >= 5)
        return true;

    int index; 
    uint16_t len_mask = 5;
    int width = getClassicBoard().getWidth();
    int size = width * width - width * (len_mask - 1);
    IBoard::bitboard mask("11111");
    for (int i = 0; i < size; ++i)
    {
        int x = i % (width - len_mask - 1), y = i / width;
        if (getClassicBoard().findMatch(x, y, player, mask, len_mask)) {
            return !checkPossibleCapture(x, y, PatternType::CLASSIC, player);
        }
        else if (getTransposedBoard().findMatch(x, y, player, mask, len_mask)) {
            return !checkPossibleCapture(x, y, PatternType::TRANSPOS, player);
        }
        else if (getDiagBoard().findMatch(x, y, player, mask, len_mask)) {
            return !checkPossibleCapture(x, y, PatternType::DIAG, player);
        }
        else if (getAntiDiagBoard().findMatch(x, y, player, mask, len_mask)) {
            return !checkPossibleCapture(x, y, PatternType::ANTIDIAG, player);
        }
    }
    return false;
}

Game::patternMap Game::extractPatterns(uint16_t x, uint16_t y, uint16_t length, uint16_t player){
    patternMap result;

    result.insert({Game::CLASSIC, this->_classicBoard.extractPattern(x, y, length, player)});
    result.insert({Game::TRANSPOS, this->_transposedBoard.extractPattern(x, y, length, player)});
    result.insert({Game::DIAG, this->_diagBoard.extractPattern(x, y, length, player)});
    result.insert({Game::ANTIDIAG, this->_antiDiagBoard.extractPattern(x, y, length, player)});
    result.insert({Game::REV_CLASSIC, this->_classicBoard.extractPatternReversed(x, y, length, player)});
    result.insert({Game::REV_TRANSPOS, this->_transposedBoard.extractPatternReversed(x, y, length, player)});
    result.insert({Game::REV_DIAG, this->_diagBoard.extractPatternReversed(x, y, length, player)});
    result.insert({Game::REV_ANTIDIAG, this->_antiDiagBoard.extractPatternReversed(x, y, length, player)});

    return result;
}

bool Game::isDoubleThree(uint16_t x, uint16_t y, uint16_t player) {
    int doubleThreeCnt = 0;
    const int opponent = player == WHITE ? BLACK : WHITE;

    patternBitset  playerPattern1("0110");
    patternBitset  playerPattern2("1100");
    patternBitset  playerPattern3("0011");

    patternMap playerPatterns = extractPatterns(x, y, 4, player);
    patternMap opponentPatterns = extractPatterns(x, y, 5, opponent);

    for (int i = 0; i < 8; i++) {
        Game::PatternType boardType = static_cast<Game::PatternType>(i);
        if (opponentPatterns[boardType] == 0 && (playerPatterns[boardType] == playerPattern1 || playerPatterns[boardType] == playerPattern2 || playerPatterns[boardType] == playerPattern3))
            doubleThreeCnt++;
        else if ((opponentPatterns[boardType] == 1 || opponentPatterns[boardType] == 16) && playerPatterns[boardType] == playerPattern1)
            doubleThreeCnt++;
    }
    return doubleThreeCnt >= 2;
}

std::vector<uint16_t> Game::isCapture(uint16_t x, uint16_t y, uint16_t player) {
    std::vector<uint16_t> capturesBoard;
    int opponent = player == WHITE ? BLACK : WHITE;

    patternBitset  playerPattern("1001");
    patternBitset  opponentPattern("0110");

    patternMap playerPatterns = extractPatterns(x, y, 4, player);
    patternMap opponentPatterns = extractPatterns(x, y, 4, opponent);

    for (int i = 0; i < 8; i++) {
        Game::PatternType boardType = static_cast<Game::PatternType>(i);
        if (playerPatterns[boardType] == playerPattern && opponentPatterns[boardType] == opponentPattern)
            capturesBoard.push_back(boardType);
    }
    return capturesBoard;
}

void Game::handleCapture(uint16_t x, uint16_t y, std::vector<uint16_t> capturesBoard, uint16_t player, Render& render) {
    const int   dirX[8] = {1, 0, 1, 1, -1, 0, -1, -1};
    const int   dirY[8] = {0, 1, -1, 1, 0, -1, 1, -1};

    for (int boardType: capturesBoard)
    {
        render.erasePlayer(x + dirX[boardType], y + dirY[boardType]);
        render.erasePlayer(x + dirX[boardType] * 2, y + dirY[boardType] * 2);
        removePosToBoards(x + dirX[boardType], y + dirY[boardType]);
        removePosToBoards(x + dirX[boardType] * 2, y + dirY[boardType] * 2);
        addCapture(player);
    }
}