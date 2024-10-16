#include "../inc/Game.hpp" 

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

uint8_t Game::getCapture(int player) {
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

ClassicBoard Game::getClassicBoard() const noexcept{
    return(this->_classicBoard);
}

TransposedBoard Game::getTransposedBoard() const noexcept{
    return(this->_transposedBoard);
}

AntiDiagBoard Game::getAntiDiagBoard() const noexcept{
    return(this->_antiDiagBoard);
}

DiagBoard Game::getDiagBoard() const noexcept{
    return(this->_diagBoard);
}

void    Game::setPosToBoards(uint8_t x, uint8_t y, int player){
    _classicBoard.setPos(x, y, player);
    _transposedBoard.setPos(x, y, player);
    _antiDiagBoard.setPos(x, y, player);
    _diagBoard.setPos(x, y, player);
}

void    Game::removePosToBoards(uint8_t x, uint8_t y){
    _classicBoard.removePos(x, y);
    _transposedBoard.removePos(x, y);
    _antiDiagBoard.removePos(x, y);
    _diagBoard.removePos(x, y);
}