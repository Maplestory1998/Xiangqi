#include "gamecontroller.h"
#include "QtDebug"

GameController::GameController() : m_board (&g_board),  m_gameState(WAIT_PLAYER_CHOOSE_PIECE), m_currentPlayer(RED)
{
    ai = nullptr;
}

GameController::~GameController()
{

}


GAME_STATE GameController::controller(int _row, int _col, GAME_MODE gameMode)
{
    if(_row < 0 || _row > 9 || _col < 0 || _col > 8)
    {
        if(m_gameState == WAIT_PLAYER_MOVE)
            m_gameState = WAIT_PLAYER_CHOOSE_PIECE;
        return m_gameState;
    }
    if(m_gameState == WAIT_PLAYER_CHOOSE_PIECE)
    {
        if(m_board->getPieceType(_row, _col) == NO_PIECE || m_board->getPieceColor(_row, _col) != m_currentPlayer)
            return m_gameState;

        m_gameState = WAIT_PLAYER_MOVE;
        setChosePos(_row, _col);
        return m_gameState;
    }
    else if(m_gameState ==  WAIT_PLAYER_MOVE)
    {
        setCurPos(_row, _col);
        bool res = getBoard()->canMove(getChosePos(), getCurPos());

        if(res == true)
        {
            m_currentPlayer = m_currentPlayer == RED? BLACK : RED;
            getBoard()->movePiece(getChosePos(), getCurPos());
            m_gameState = gameMode == PVP ?WAIT_PLAYER_CHOOSE_PIECE: WAIT_AI_MOVE;
        }


    }
    //判断游戏是否结束
    if(m_board->getPiece(4).isExist() == false) {
         qDebug()<<"Red win";
         m_gameState = RED_WIN;
    }

    if(m_board->getPiece(20).isExist() == false) {
        qDebug()<<"Black win";
        m_gameState = BLACK_WIN;
    }

    return m_gameState;
}


void GameController::setBoard(Board *_board){
    delete m_board;
    m_board = new Board(*_board);;
}
