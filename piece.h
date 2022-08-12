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
    Piece& operator=(const Piece& _p);
    ~Piece();


    PIECE_COLOR getColor(){
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

    pair<int, int> getPos() {
        return pos;
    }
    void setPos(int row, int col) {
        pos.first = row;
        pos.second = col;
    }
    void setPos(pair<int,int> &_pos) {
        pos = _pos;
    }

public:
    Board *m_board;
private:
    //position
    pair<int, int> pos;

    PIECE_TYPE m_type;
    //棋子是否仍存在
    bool m_exist;

};

bool canGeneralMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color,Board *board);
bool canAdvisorMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board);
bool canElephantMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board);
bool canHorseMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board);
bool canChariotMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board);
bool canCannoMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board);
bool canSoldierMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board);

void getGeneralMove(pair<int,int> oldP,  PIECE_COLOR color, Board* board, vector<ChessMove>& chessMove);
void getAdvisorMove(pair<int, int> oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getElephantMove(pair<int, int> oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getHorseMove(pair<int, int> oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getChariotMove(pair<int, int> oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getCannoMove(pair<int, int> oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);
void getSoldierMove(pair<int, int> oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove);


bool isOnBoard(pair<int, int> &p);
bool isEmptyOrEnemy(Board* board, PIECE_COLOR color, pair<int, int> pos);

#endif // PIECE_H
