#ifndef BOARD_H
#define BOARD_H
#include <QPoint>
#include <QPair>
#include <QPixmap>
#include "piece.h"

extern InitialPos g_initialPos[32];

class Board
{
public:
    Board();
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
    }

    void setPieceType(int row, int col, PIECE_TYPE type)
    {
        m_pieceType[row][col] = type;
    }

    //获取位置为row，col的棋子类型
    inline PIECE_TYPE getPieceType(int row, int col)
    {
        if(row < 0 || row > 9 || col < 0 || col > 8)
            return NO_PIECE;
        return m_pieceType[row][col];
    }

    //获取位置为row，col的棋子颜色
    PIECE_COLOR getPieceColor(int row, int col)
    {
        int idx = m_chessBoard[row][col];
        return m_pieces[idx].getColor();
    }

    //棋子能否从oldP移动到newP
    bool canMove(QPair<int,int> oldP, QPair<int, int> newP);
    void init();

    //移动棋子
    void movePiece(QPair<int, int> oldP, QPair<int, int> newP);

    //获取id为idx的棋子
    Piece& getPiece(int idx){
        return m_pieces[idx];
    }

private:
    //存储每个位置的棋子id
    int m_chessBoard[10][9]; //store Piece idx of every board position
    //存储每个位置的棋子类型
    PIECE_TYPE m_pieceType[10][9];
    //存储每个棋子的位置
    Piece m_pieces[32];   //store the position info of 32 pieces

    void initBoard();
};

extern Board g_board;



#endif // BOARD_H
