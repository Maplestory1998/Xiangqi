#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <QPoint>
#include "board.h"
#include "ai.h"
enum GAME_MODE{
    PVP,
    PVE,
};


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
    void setBoard(Board *_board);
    void setGameState(GAME_STATE state){m_gameState = state;}
    GAME_STATE getGameState(){return m_gameState;}

    GAME_STATE controller(int _row, int _col, GAME_MODE gameMode);

    pair<int, int> getChosePos() { return m_chosePos;}
    pair<int, int> getCurPos() { return m_curPos;}

    void setChosePos(int r, int c) {m_chosePos = {r, c};}
    void setCurPos(int r, int c) { m_curPos = {r, c};}

    Ai* ai;

private:

    Board *m_board;
    //PVP or PVE
    GAME_STATE m_gameState;

    pair<int, int> m_chosePos;
    pair<int, int> m_curPos;
    //轮到谁走棋了
    PIECE_COLOR m_currentPlayer;

};

#endif // GAMECONTROLLER_H
