#include "../inc/Game.hpp"

#include "../inc/IBoard.hpp"

Game::Game()
    : _classicBoard()
    , _transposedBoard()
    , _antiDiagBoard()
    , _diagBoard()
    , _player1Capture(0)
    , _player2Capture(0)
    , _heuristic(0)
{
}

Game::~Game() { }

Game::Game(const Game& cpy)
    : _classicBoard(cpy._classicBoard)
    , _transposedBoard(cpy._transposedBoard)
    , _antiDiagBoard(cpy._antiDiagBoard)
    , _diagBoard(cpy._diagBoard)
    , _player1Capture(cpy._player1Capture)
    , _player2Capture(cpy._player2Capture)
    , _heuristic(cpy._heuristic)
{
}

Game& Game::operator=(const Game& rhs)
{
    if (this != &rhs) {
        this->_classicBoard = rhs._classicBoard;
        this->_transposedBoard = rhs._transposedBoard;
        this->_antiDiagBoard = rhs._antiDiagBoard;
        this->_diagBoard = rhs._diagBoard;
        this->_player1Capture = rhs._player1Capture;
        this->_player2Capture = rhs._player2Capture;
        this->_heuristic = rhs._heuristic;
    }
    return (*this);
}

bool Game::operator==(Game& rhs)
{
    if (getClassicBoard() == rhs.getClassicBoard())
        return true;
    return false;
}

uint16_t
Game::getCapture(int player)
{
    if (player == this->getClassicBoard().getIdPlayer1())
        return _player1Capture;
    else if (player == this->getClassicBoard().getIdPlayer2())
        return _player2Capture;
    return 0;
}

void Game::addCapture(int player)
{
    if (player == this->getClassicBoard().getIdPlayer1())
        _player1Capture++;
    else if (player == this->getClassicBoard().getIdPlayer2())
        _player2Capture++;
}

ClassicBoard&
Game::getClassicBoard() noexcept
{
    return (this->_classicBoard);
}

TransposedBoard&
Game::getTransposedBoard() noexcept
{
    return (this->_transposedBoard);
}

AntiDiagBoard&
Game::getAntiDiagBoard() noexcept
{
    return (this->_antiDiagBoard);
}

DiagBoard&
Game::getDiagBoard() noexcept
{
    return ((this->_diagBoard));
}

void Game::setPosToBoards(uint16_t x, uint16_t y, int player)
{
    _classicBoard.setPos(x, y, player);
    _transposedBoard.setPos(x, y, player);
    _antiDiagBoard.setPos(x, y, player);
    _diagBoard.setPos(x, y, player);
}

void Game::removePosToBoards(uint16_t x, uint16_t y)
{
    _classicBoard.removePos(x, y);
    _transposedBoard.removePos(x, y);
    _antiDiagBoard.removePos(x, y);
    _diagBoard.removePos(x, y);
}

void Game::resetBoards()
{
    _classicBoard.resetBoard();
    _transposedBoard.resetBoard();
    _antiDiagBoard.resetBoard();
    _diagBoard.resetBoard();
}

size_t
Game::hashGame() const
{
    std::size_t h1 = std::hash<IBoard::bitboard> {}(this->_classicBoard.getPlayer1());
    std::size_t h2 = std::hash<IBoard::bitboard> {}(this->_classicBoard.getPlayer2());
    return h1 ^ (h2 << 1);
}

void Game::setHeuristic(int64_t heuristic)
{
    this->_heuristic = heuristic;
}

int64_t
Game::getHeuristic() const
{
    return this->_heuristic;
}

bool Game::isFull() const
{
    IBoard::bitboard fullBoard = this->_classicBoard.getPlayer1() | this->_classicBoard.getPlayer2();
    return (fullBoard.count() == this->_classicBoard.getWidth() * this->_classicBoard.getWidth());
}

bool Game::canBeCaptured(uint16_t x,
    uint16_t y,
    Game::PatternType boardType,
    uint16_t player)
{
    const int opponent = (player == WHITE) ? BLACK : WHITE;
    const int dirX[8] = { 1, 0, 1, 1, -1, 0, -1, -1 };
    const int dirY[8] = { 0, 1, -1, 1, 0, -1, 1, -1 };
    for (int i = 0; i < 5; i++) {
        x = x + dirX[boardType];
        y = y + dirY[boardType];

        // std::cout << "X: " << x << " Y: " << y << std::endl;
        if (!getClassicBoard().isValidPos(x, y))
            continue;

        for (int j = 0; j < 4; j++) {
            // Forward check
            const uint16_t xFwd1 = x + dirX[j], yFwd1 = y + dirY[j];
            const uint16_t xFwd2 = xFwd1 + dirX[j], yFwd2 = yFwd1 + dirY[j];
            const uint16_t xOpp1 = x + dirX[j + 4], yOpp1 = y + dirY[j + 4];

            if (getClassicBoard().isValidPos(xOpp1, yOpp1) && getClassicBoard().isValidPos(xFwd2, yFwd2)) {
                if ((getClassicBoard().getPos(xOpp1, yOpp1) == opponent && getClassicBoard().getPos(xFwd1, yFwd1) == player && getClassicBoard().getPos(xFwd2, yFwd2) == EMPTY) || (getClassicBoard().getPos(xOpp1, yOpp1) == EMPTY && getClassicBoard().getPos(xFwd1, yFwd1) == player && getClassicBoard().getPos(xFwd2, yFwd2) == opponent)) {
                    return true;
                }
            }

            // Reverse check
            const uint16_t xRev1 = x + dirX[j + 4], yRev1 = y + dirY[j + 4];
            const uint16_t xRev2 = xRev1 + dirX[j + 4], yRev2 = yRev1 + dirY[j + 4];
            const uint16_t xOpp2 = x + dirX[j], yOpp2 = y + dirY[j];

            if (getClassicBoard().isValidPos(xOpp2, yOpp2) && getClassicBoard().isValidPos(xRev2, yRev2)) {
                if ((getClassicBoard().getPos(xOpp2, yOpp2) == opponent && getClassicBoard().getPos(xRev1, yRev1) == player && getClassicBoard().getPos(xRev2, yRev2) == EMPTY) || (getClassicBoard().getPos(xOpp2, yOpp2) == EMPTY && getClassicBoard().getPos(xRev1, yRev1) == player && getClassicBoard().getPos(xRev2, yRev2) == opponent)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::playerWin(uint16_t player)
{
    if (getCapture(player) >= 5)
        return true;

    const uint16_t len_mask = 5;
    const int width = getClassicBoard().getWidth();
    const int size = width * width - width * (len_mask - 1);
    IBoard::bitboard mask("11111");
    for (int i = 0; i < size; ++i) {
        int x = i % (width - len_mask - 1), y = i / width;
        if (getClassicBoard().findMatch(x, y, player, mask, len_mask))
            return !canBeCaptured(x, y, PatternType::CLASSIC, player);

        if (getTransposedBoard().findMatch(x, y, player, mask, len_mask))
            return !canBeCaptured(x, y, PatternType::TRANSPOS, player);

        if (getDiagBoard().findMatch(x, y, player, mask, len_mask))
            return !canBeCaptured(x, y, PatternType::DIAG, player);

        if (getAntiDiagBoard().findMatch(x, y, player, mask, len_mask))
            return !canBeCaptured(x, y, PatternType::ANTIDIAG, player);
    }
    return false;
}

Game::patternMap
Game::extractPatterns(uint16_t x, uint16_t y, uint16_t length, uint16_t player)
{
    patternMap result;

    result.insert({ Game::CLASSIC,
        this->_classicBoard.extractPattern(x, y, length, player) });
    result.insert(
        { Game::TRANSPOS,
            this->_transposedBoard.extractPattern(x, y, length, player) });
    result.insert(
        { Game::DIAG, this->_diagBoard.extractPattern(x, y, length, player) });
    result.insert({ Game::ANTIDIAG,
        this->_antiDiagBoard.extractPattern(x, y, length, player) });
    result.insert(
        { Game::REV_CLASSIC,
            this->_classicBoard.extractPatternReversed(x, y, length, player) });
    result.insert(
        { Game::REV_TRANSPOS,
            this->_transposedBoard.extractPatternReversed(x, y, length, player) });
    result.insert(
        { Game::REV_DIAG,
            this->_diagBoard.extractPatternReversed(x, y, length, player) });
    result.insert(
        { Game::REV_ANTIDIAG,
            this->_antiDiagBoard.extractPatternReversed(x, y, length, player) });

    return result;
}

bool Game::isDoubleThree(uint16_t x, uint16_t y, uint16_t player)
{
    int doubleThreeCnt = 0;
    const int opponent = (player == WHITE) ? BLACK : WHITE;

    const patternBitset playerPattern1("0110");
    const patternBitset playerPattern2("1100");
    const patternBitset playerPattern3("0011");

    patternMap playerPatternMap = extractPatterns(x, y, 4, player);
    patternMap opponentPatternMap = extractPatterns(x, y, 5, opponent);

    for (int i = 0; i < 4; i++) {
        Game::PatternType boardType = static_cast<Game::PatternType>(i);
        Game::PatternType boardTypeRev = static_cast<Game::PatternType>(i + 4);
        if (opponentPatternMap[boardType] == 0 && (playerPatternMap[boardType] == playerPattern1 || playerPatternMap[boardType] == playerPattern2 || playerPatternMap[boardType] == playerPattern3))
            doubleThreeCnt++;
        else if ((opponentPatternMap[boardType] == 1 || opponentPatternMap[boardType] == 16) && playerPatternMap[boardType] == playerPattern1)
            doubleThreeCnt++;
        else if (opponentPatternMap[boardTypeRev] == 0 && (playerPatternMap[boardTypeRev] == playerPattern1 || playerPatternMap[boardTypeRev] == playerPattern2 || playerPatternMap[boardTypeRev] == playerPattern3))
            doubleThreeCnt++;
        else if ((opponentPatternMap[boardTypeRev] == 1 || opponentPatternMap[boardTypeRev] == 16) && playerPatternMap[boardTypeRev] == playerPattern1)
            doubleThreeCnt++;
    }
    return doubleThreeCnt >= 2;
}

std::vector<uint16_t>
Game::isCapture(uint16_t x, uint16_t y, uint16_t player)
{
    std::vector<uint16_t> capturesBoard;
    const int opponent = (player == WHITE) ? BLACK : WHITE;

    const patternBitset playerPattern("1001");
    const patternBitset opponentPattern("0110");

    patternMap playerPatternMap = extractPatterns(x, y, 4, player);
    patternMap opponentPatternMap = extractPatterns(x, y, 4, opponent);

    for (int i = 0; i < 8; i++) {
        Game::PatternType boardType = static_cast<Game::PatternType>(i);
        if (playerPatternMap[boardType] == playerPattern && opponentPatternMap[boardType] == opponentPattern)
            capturesBoard.push_back(boardType);
    }
    return capturesBoard;
}

bool Game::canCapture(uint16_t x, uint16_t y, uint16_t player)
{
    if (!getClassicBoard().isPosEmpty(x, y))
        return false;

    setPosToBoards(x, y, player);
    const int opponent = (player == WHITE) ? BLACK : WHITE;

    const patternBitset playerPattern("1001");
    const patternBitset opponentPattern("0110");

    patternMap playerPatternMap = extractPatterns(x, y, 4, player);
    patternMap opponentPatternMap = extractPatterns(x, y, 4, opponent);

    for (int i = 0; i < 8; i++) {
        Game::PatternType boardType = static_cast<Game::PatternType>(i);
        if (playerPatternMap[boardType] == playerPattern && opponentPatternMap[boardType] == opponentPattern) {
            removePosToBoards(x, y);
            return true;
        }
    }
    removePosToBoards(x, y);
    return false;
}

void Game::handleCapture(uint16_t x,
    uint16_t y,
    std::vector<uint16_t>& capturesBoard,
    uint16_t player,
    Render& render)
{
    const int dirX[8] = { 1, 0, 1, 1, -1, 0, -1, -1 };
    const int dirY[8] = { 0, 1, -1, 1, 0, -1, 1, -1 };

    for (int boardType : capturesBoard) {
        render.erasePlayer(x + dirX[boardType], y + dirY[boardType]);
        render.erasePlayer(x + dirX[boardType] * 2, y + dirY[boardType] * 2);
        removePosToBoards(x + dirX[boardType], y + dirY[boardType]);
        removePosToBoards(x + dirX[boardType] * 2, y + dirY[boardType] * 2);
        addCapture(player);
        render.renderCapture(getCapture(WHITE), getCapture(BLACK));
    }
}

bool checkPatternAtPosition(const patternMerge& playerLine,
    const patternMerge& opponentLine,
    t_pattern pattern,
    int startPos)
{
    if (startPos < 0 || startPos > MERGE_SIZE)
        return false;
    patternMerge mask((1 << pattern.length) - 1);

    patternMerge playerShiftedPattern(playerLine.to_ulong() >> (9 - startPos));
    patternMerge opponentShiftedPattern(opponentLine.to_ulong() >> (9 - startPos));
    playerShiftedPattern &= mask;
    opponentShiftedPattern &= mask;

    // std::cout << startPos << ": " << playerShiftedPattern << "      " <<
    // opponentShiftedPattern << std::endl;
    return playerShiftedPattern == pattern.player && opponentShiftedPattern == pattern.opponent;
}

int Game::heuristicTest(int x, int y, int player)
{
    int counter = 0;
    const int opponent = (player == WHITE) ? BLACK : WHITE;
    patternMap extractPlayer = extractPatterns(x, y, PATTERN_SIZE, player);
    patternMap extractOpponent = extractPatterns(x, y, PATTERN_SIZE, opponent);

    for (const t_pattern& pattern : patternsArray) {
        for (int i = 0; i < 4; i++) {
            patternBitset boardPlayerPattern = extractPlayer[static_cast<Game::PatternType>(i)];
            patternBitset revBoardPlayerPattern = extractPlayer[static_cast<Game::PatternType>(i + 4)];
            patternMerge mergedPlayerPattern = (boardPlayerPattern.to_ulong() << 4 | revBoardPlayerPattern.to_ulong());

            patternBitset boardOpponentPattern = extractOpponent[static_cast<Game::PatternType>(i)];
            patternBitset revBoardOpponentPattern = extractOpponent[static_cast<Game::PatternType>(i + 4)];
            patternMerge mergedOpponentPattern = (boardOpponentPattern.to_ulong() << 4 | revBoardOpponentPattern.to_ulong());

            for (int i = 0; i < pattern.length; i++) {
                if (checkPatternAtPosition(
                        mergedPlayerPattern, mergedOpponentPattern, pattern, 5 - i)) {
                    counter += pattern.value;
                    // std::cout << "PLAYER: " << ((player == WHITE) ? "WHITE" : "BLACK")
                    // << " | FIND: " << pattern.value << " | PLAYER PATTERN: " <<
                    // pattern.player << " | OPP PATTERN: " << pattern.opponent <<
                    // std::endl;
                    break;
                }
                if (checkPatternAtPosition(
                        mergedPlayerPattern, mergedOpponentPattern, pattern, 5 + i)) {
                    counter += pattern.value;
                    // std::cout << "PLAYER: " << ((player == WHITE) ? "WHITE" : "BLACK")
                    // << " | FIND: " << pattern.value << " | PLAYER PATTERN: " <<
                    // pattern.player << " | OPP PATTERN: " << pattern.opponent <<
                    // std::endl;
                    break;
                }
            }
        }
    }
    return counter;
}

int Game::globalHeurisitic(int player)
{
    int result = 0;
    const int opponent = (player == WHITE) ? BLACK : WHITE;
    const int width = getClassicBoard().getWidth();

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < width; y++) {
            if (getClassicBoard().getPos(x, y) == player) {
                result += heuristicTest(x, y, player);
            } else if (getClassicBoard().getPos(x, y) == opponent) {
                result -= heuristicTest(x, y, opponent);
            }
        }
    }
    return result;
}
