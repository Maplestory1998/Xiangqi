#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <QPoint>
#include "board.h"
#include "ai.h"

class Ai;
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


class GameController {
public:
    GameController(GAME_MODE mode);
    ~GameController();

    inline Board* getBoard() { 
        return m_board;
    }

    inline void setGameState(GAME_STATE state) {
        m_gameState = state;
    }

    inline GAME_STATE getGameState() {
        return m_gameState;
    }

    inline pair<int, int> getChosePos() { 
        return m_chosePos;
    }

    inline pair<int, int> getCurPos() { 
        return m_curPos;
    }

    inline void setChosePos(int r, int c) {
        m_chosePos = {r, c};
    }

    inline void setCurPos(int r, int c) { 
        m_curPos = {r, c};
    }

    void setBoard(Board *_board);

    GAME_STATE controller(int _row, int _col, GAME_MODE gameMode);

    void runAi(PIECE_COLOR _aiColor);

private:
    Board *m_board;
    GAME_STATE m_gameState;

    pair<int, int> m_chosePos;
    pair<int, int> m_curPos;

public:
    Ai* ai;
    PIECE_COLOR m_currentPlayer;

    bool isOpenChosePos;
    bool isOpenCurPos;
};

#endif // GAMECONTROLLER_H
