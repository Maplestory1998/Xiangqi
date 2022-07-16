#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <QPoint>
#include "board.h"

enum GAME_STATE{
    WAIT_PLAYER_CHOOSE_PIECE,
    WAIT_PLAYER_MOVE,
    WAIT_AI_MOVE,
    BLACK_WIN,
    RED_WIN,
};


class GameController
{
public:
    GameController();
    ~GameController();
    Board* getBoard() { return m_board;}
    void setGameState(GAME_STATE state){m_gameState = state;}
    GAME_STATE getGameState(){return m_gameState;}

    GAME_STATE controller(int _row, int _col);

    QPair<int, int> getChosePos() { return m_chosePos;}
    QPair<int, int> getCurPos() { return m_curPos;}

    void setChosePos(int r, int c) {m_chosePos = {r, c};}
    void setCurPos(int r, int c) { m_curPos = {r, c};}

private:

    Board *m_board;

    GAME_STATE m_gameState;

    QPair<int, int> m_chosePos;
    QPair<int, int> m_curPos;

    PIECE_COLOR m_currentPlayer;

};

#endif // GAMECONTROLLER_H
