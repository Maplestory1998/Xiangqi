#ifndef BOARD_H
#define BOARD_H
#include <QPoint>
#include <utility>
#include <QPixmap>
#include "piece.h"

extern InitialPos g_initialPos[32];

class Board
{
public:
    Board();
    Board(const Board &b);
    Board& operator=(const Board &b);
    ~Board(){};

    //获取位置为row，col的棋子id
    inline int getPieceID(int row, int col)
    {
        if(row < 0 || row > 9 || col < 0 || col > 8)
            return -1;

        return m_chessBoard[row][col];
    }

    void setPieceID(int row, int col, int idx)
    {
        m_chessBoard[row][col] = idx;
        if (idx != -1)
            m_pieces[idx].setPos(row, col);
    }

    //获取位置为row，col的棋子类型
    inline PIECE_TYPE getPieceType(int row, int col)
    {
        int pieceId = getPieceID(row, col);
        return pieceId == -1? NO_PIECE : m_pieces[pieceId].getType();
    }

    inline PIECE_TYPE getPieceType(const pair<int,int> p) {
        return getPieceType(p.first, p.second);
    }

    //获取位置为row，col的棋子颜色
    PIECE_COLOR getPieceColor(int row, int col)
    {
        int idx = m_chessBoard[row][col];
        return m_pieces[idx].getColor();
    }

    //棋子能否从oldP移动到newP
    bool canMove(const pair<int,int> &oldP, const pair<int, int> &newP);

    //移动棋子
    void movePiece(const pair<int, int> &oldP, const pair<int, int> &newP);

    void movePiece(const ChessMove &chessMove);

    //获取id为idx的棋子
    Piece& getPiece(int idx){
        return m_pieces[idx];
    }

private:
    void copyOrAssign(const Board &b);
    void initBoard();

private:
    //存储每个位置的棋子id
    int m_chessBoard[10][9]; //store Piece idx of every board position
    //存储每个棋子的位置
    Piece m_pieces[32];   //store the position info of 32 pieces
};

extern Board g_board;



#endif // BOARD_H
