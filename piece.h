#ifndef PIECE_H
#define PIECE_H
#include <QString>
#include <utility>
#include <QVector>
#include <vector>
using namespace std;

class Board;
extern Board g_board;

struct ChessMove{
    ChessMove(pair<int, int> _from, pair<int, int> _to):
         from(_from), to(_to){
    }
    pair<int, int> from;
    pair<int, int> to;
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


typedef bool (*callback)(pair<int, int> oldP, pair<int, int> newP, PIECE_COLOR color,Board *board);

typedef void (*callback2)(pair<int,int> oldP, PIECE_COLOR color, Board* board, vector<ChessMove>& chessMove);

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
    Piece(const Piece &piece);
    PIECE_COLOR getColor(){return m_color;}
    PIECE_TYPE getType(){return m_type;}
    void Init(int id);

    bool isExist(){return m_exist;}
    void destroyPiece(){m_exist = false;}

    callback canPieceMove;
    callback2 allMoveMethod;
    Board *m_board;
private:
    PIECE_TYPE m_type;
    PIECE_COLOR m_color;

    //棋子是否仍存在
    bool m_exist;

};

bool canGeneralMove(pair<int, int> oldP, pair<int, int> newP, PIECE_COLOR color,Board *board);
bool canAdvisorMove(pair<int, int> oldP, pair<int, int> newP, PIECE_COLOR color, Board *board);
bool canElephantMove(pair<int, int> oldP, pair<int, int> newP, PIECE_COLOR color, Board *board);
bool canHorseMove(pair<int, int> oldP, pair<int, int> newP, PIECE_COLOR color, Board *board);
bool canChariotMove(pair<int, int> oldP, pair<int, int> newP, PIECE_COLOR color, Board *board);
bool canCannoMove(pair<int, int> oldP, pair<int, int> newP, PIECE_COLOR color, Board *board);
bool canSoldierMove(pair<int, int> oldP, pair<int, int> newP, PIECE_COLOR color, Board *board);

void getGeneralMove(pair<int,int> oldP,  PIECE_COLOR color, Board* board, vector<ChessMove>& chessMove);
void getAdvisorMove(pair<int, int> oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getElephantMove(pair<int, int> oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getHorseMove(pair<int, int> oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getChariotMove(pair<int, int> oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getCannoMove(pair<int, int> oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getSoldierMove(pair<int, int> oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);


bool isOnBoard(pair<int, int> p);
bool isEmptyOrEnemy(Board* board, PIECE_COLOR color, pair<int, int> pos);

#endif // PIECE_H
