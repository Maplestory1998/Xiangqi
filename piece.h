#ifndef PIECE_H
#define PIECE_H
#include <QString>
#include <QPair>
#include <QVector>
#include <vector>
using namespace std;

class Board;
extern Board g_board;

struct ChessMove{
    ChessMove(QPair<int, int> _from, QPair<int, int> _to):
         from(_from), to(_to){
    }
    QPair<int, int> from;
    QPair<int, int> to;
};

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

typedef void (*callback2)(QPair<int,int> oldP, PIECE_COLOR color, Board* board, vector<ChessMove>& chessMove);

struct InitialPos{
    int row, col;
    PIECE_TYPE type;
    callback func;
    callback2 func2;
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
    callback2 allMoveMethod;
private:
    PIECE_TYPE m_type;
    PIECE_COLOR m_color;

    //棋子是否仍存在
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

void getGeneralMove(QPair<int,int> oldP,  PIECE_COLOR color, Board* board, vector<ChessMove>& chessMove);
void getAdvisorMove(QPair<int, int> oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getElephantMove(QPair<int, int> oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getHorseMove(QPair<int, int> oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getChariotMove(QPair<int, int> oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getCannoMove(QPair<int, int> oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getSoldierMove(QPair<int, int> oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);


bool isOnBoard(QPair<int, int> p);
bool isEmptyOrEnemy(Board* board, PIECE_COLOR color, QPair<int, int> pos);

#endif // PIECE_H
