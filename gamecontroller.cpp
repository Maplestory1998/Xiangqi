#include "gamecontroller.h"
#include "QtDebug"

GameController::GameController(GAME_MODE mode) : m_board (&g_board),  m_gameState(WAIT_PLAYER_CHOOSE_PIECE), m_currentPlayer(RED), ai(nullptr) {
    if (mode == PVE) {
        ai = new Ai(m_board, BLACK);
    }
}

GameController::~GameController() {
    delete ai;
    if (m_board != &g_board) {
        delete m_board;
    }
}

void GameController::runAi(PIECE_COLOR _aiColor) {
    ai->run(_aiColor);
    m_gameState = WAIT_PLAYER_CHOOSE_PIECE;
    m_currentPlayer = m_currentPlayer == RED? BLACK : RED;
}


/**
 * @brief Game Controller, called when the player choose piece
 * 
 * @param _row 
 * @param _col 
 * @param gameMode 
 * @return GAME_STATE 
 */
GAME_STATE GameController::controller(int _row, int _col, GAME_MODE gameMode) {
    if(m_gameState == WAIT_PLAYER_CHOOSE_PIECE) {
        if (_row < 0 || _row > 9 || _col < 0 || _col > 8 ||
                m_board->getPieceType(_row, _col) == NO_PIECE ||
                m_board->getPieceColor(_row, _col) != m_currentPlayer)
            return m_gameState;

        m_gameState = WAIT_PLAYER_MOVE;
        setChosePos(_row, _col);
        return m_gameState;
    } else if(m_gameState ==  WAIT_PLAYER_MOVE) {
        if (_row < 0 || _row > 9 || _col < 0 || _col > 8) {
            m_gameState = WAIT_PLAYER_CHOOSE_PIECE;
            return m_gameState;
        }

        setCurPos(_row, _col);
        bool res = getBoard()->canMove(getChosePos(), getCurPos());

        if(res == true) {
            m_currentPlayer = m_currentPlayer == RED? BLACK : RED;
            getBoard()->movePiece(getChosePos(), getCurPos());
            m_gameState = gameMode == PVP ?WAIT_PLAYER_CHOOSE_PIECE: WAIT_AI_MOVE;
        }
    }
    //判断游戏是否结束
    if(m_board->getPiece(4).isExist() == false) {
         m_gameState = RED_WIN;
    }

    if(m_board->getPiece(20).isExist() == false) {
        m_gameState = BLACK_WIN;
    }

    return m_gameState;
}


void GameController::setBoard(Board *_board){
    *m_board = *_board; 
    delete m_board;
}
