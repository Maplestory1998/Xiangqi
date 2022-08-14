#ifndef PIECE_H
#define PIECE_H
#include <QString>
#include <utility>
#include <QVector>
#include <vector>
using namespace std;

class Board;
extern Board g_board;

/**
 * @brief move method
 * 
 */
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
    NO_COLOR,
    RED,
    BLACK,
};

/**
 * @brief Determine whether the piece can be moved from oldP to newP
 * 
 */
typedef bool (*callback)(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board);

/**
 * @brief Get all moves of the piece
 * 
 */
typedef void (*callback2)(const pair<int,int> &oldP, PIECE_COLOR color, Board* board, vector<ChessMove>& chessMove);

typedef int (*callback3)(const pair<int,int> &oldP, PIECE_COLOR color, Board *board);


struct InitialPos{
    int row, col;
    PIECE_TYPE type;
    callback func;
    callback2 func2;
    callback3 func3;
    int value;
    int flexibilityFactor;
    int (*posEvalutaion)[9];
    int maxMoveMethod;
};

extern InitialPos g_initialPos[32];
extern QString g_imagesSources[14];

extern int chariotPosValue[10][9];
extern int horsePosValue[10][9];
extern int cannoPosValue[10][9];
extern int soldierPosValue[10][9];
extern int generalPosValue[10][9];
extern int advisorPosValue[10][9];
extern int elephantPosValue[10][9];

class Piece
{
public:
    Piece();
    Piece(const Piece &piece);
    Piece& operator=(const Piece& _p);
    ~Piece();


    PIECE_COLOR getColor(){
        if (m_type == NO_PIECE)
            return NO_COLOR;
        PIECE_COLOR color = m_type <= BLACK_SOLDIER? BLACK : RED;
        return color;
    }
    PIECE_TYPE getType(){return m_type;}
    void Init(int id);

    bool isExist(){return m_exist;}
    void destroyPiece(){
        m_exist = false;
        m_type = NO_PIECE;
    }

    callback canPieceMove;
    callback2 allMoveMethod;
    callback3 getMoveMethodCnt;
    int (*posEvalutaion)[9];

    pair<int, int> getPos() {
        return pos;
    }
    void setPos(int row, int col) {
        pos.first = row;
        pos.second = col;
    }
    void setPos(const pair<int,int> &_pos) {
        pos = _pos;
    }

    void setBoard(Board *_b) {
        m_board = _b;
    }

    int getValue(){return value;}
    int getFlexibilityFactor(){return flexibilityFactor;}
    int getMaxMoveMethod(){return maxMoveMethod;}

public:
    Board *m_board;
private:
    //position
    pair<int, int> pos;

    PIECE_TYPE m_type;
    //棋子是否仍存在
    bool m_exist;

    int value;
    int flexibilityFactor;
    int maxMoveMethod;
};

bool canGeneralMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color,Board *board);
bool canAdvisorMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board);
bool canElephantMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board);
bool canHorseMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board);
bool canChariotMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board);
bool canCannoMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board);
bool canSoldierMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board);

void getGeneralMove(const pair<int,int> &oldP,  PIECE_COLOR color, Board* board, vector<ChessMove>& chessMove);
void getAdvisorMove(const pair<int, int> &oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getElephantMove(const pair<int, int> &oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getHorseMove(const pair<int, int> &oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getChariotMove(const pair<int, int> &oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getCannoMove(const pair<int, int> &oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getSoldierMove(const pair<int, int> &oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);


int getGeneralMoveMethodsCnt(const pair<int,int> &oldP, PIECE_COLOR color, Board *board);
int getAdvisorMoveMethodsCnt(const pair<int,int> &oldP, PIECE_COLOR color, Board *board);
int getElephantMoveMethodsCnt(const pair<int,int> &oldP, PIECE_COLOR color, Board *board);
int getHorseMoveMethodsCnt(const pair<int,int> &oldP, PIECE_COLOR color, Board *board);
int getChariotMoveMethodsCnt(const pair<int,int> &oldP, PIECE_COLOR color, Board *board);
int getCannoMoveMethodsCnt(const pair<int,int> &oldP, PIECE_COLOR color, Board *board);
int getSoldierMoveMethodsCnt(const pair<int,int> &oldP, PIECE_COLOR color, Board *board);



bool isOnBoard(pair<int, int> &p);
bool isEmptyOrEnemy(Board* board, PIECE_COLOR color, pair<int, int> pos);

#endif // PIECE_H
