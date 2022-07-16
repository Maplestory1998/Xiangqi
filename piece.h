#ifndef PIECE_H
#define PIECE_H
#include <QString>
#include <QPair>
#include <QVector>

class Board;
extern Board g_board;


enum PIECE_TYPE{
    NO_PIECE = -1,

    BLACK_GENERAL,
    BLACK_ADVISOR,
    BLACK_ELEPHANT,
    BLACK_HORSE,
    BLACK_CHARIOT,
    BLACK_CANNON,
    BLACK_SOLDIER,

    RED_GENERAL ,
    RED_ADVISOR,
    RED_ELEPHANT,
    RED_HORSE,
    RED_CHARIOT,
    RED_CANNON,
    RED_SOLDIER,
};

enum PIECE_COLOR
{
    RED,
    BLACK,
};


typedef bool (*callback)(QPair<int, int> oldP, QPair<int, int> newP, PIECE_COLOR color,Board *board);

struct InitialPos{
    int row, col;
    PIECE_TYPE type;
    callback func;

};

extern InitialPos g_initialPos[32];
extern QString g_imagesSources[14];

class Piece
{
public:
    Piece();
    PIECE_COLOR getColor(){return m_color;}
    PIECE_TYPE getType(){return m_type;}
    void Init(int id);

    bool isExist(){return m_exist;}
    void destroyPiece(){m_exist = false;}

    callback canPieceMove;
private:
    PIECE_TYPE m_type;
    PIECE_COLOR m_color;

    bool m_exist;

    Board *m_board;
};

bool canGeneralMove(QPair<int, int> oldP, QPair<int, int> newP, PIECE_COLOR color,Board *board);
bool canAdvisorMove(QPair<int, int> oldP, QPair<int, int> newP, PIECE_COLOR color, Board *board);
bool canElephantMove(QPair<int, int> oldP, QPair<int, int> newP, PIECE_COLOR color, Board *board);
bool canHorseMove(QPair<int, int> oldP, QPair<int, int> newP, PIECE_COLOR color, Board *board);
bool canChariotMove(QPair<int, int> oldP, QPair<int, int> newP, PIECE_COLOR color, Board *board);
bool canCannoMove(QPair<int, int> oldP, QPair<int, int> newP, PIECE_COLOR color, Board *board);
bool canSoldierMove(QPair<int, int> oldP, QPair<int, int> newP, PIECE_COLOR color, Board *board);



#endif // PIECE_H
