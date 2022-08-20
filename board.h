#ifndef BOARD_H
#define BOARD_H
#include <QPoint>
#include <utility>
#include <QPixmap>
#include "piece.h"

//Initial for the board and pieces
extern InitialPos g_initialPos[32];

class Board
{
public:
    Board();
    Board(const Board &b);
    Board& operator=(const Board &b);
    ~Board(){};

    
    inline int getPieceID(int row, int col) {
        return (row < 0 || row > 9 || col < 0 || col > 8)? -1 : m_chessBoard[row][col];
    }

    inline void setPieceID(int row, int col, int idx) {
        m_chessBoard[row][col] = idx;
        if (idx != -1) {
            m_pieces[idx].setPos(row, col);
        }
    }

    inline PIECE_TYPE getPieceType(int row, int col) {
        int pieceId = getPieceID(row, col);
        return pieceId == -1? NO_PIECE : m_pieces[pieceId].getType();
    }

    inline PIECE_TYPE getPieceType(const pair<int,int> p) {
        return getPieceType(p.first, p.second);
    }

    inline PIECE_COLOR getPieceColor(int row, int col) {
        int idx = m_chessBoard[row][col];
        return m_pieces[idx].getColor();
    }

    inline Piece& getPiece(int idx){
        return m_pieces[idx];
    }

    bool canMove(const pair<int,int> &oldP, const pair<int, int> &newP);

    void movePiece(const pair<int, int> &oldP, const pair<int, int> &newP);

    void movePiece(const ChessMove &chessMove);


private:
    void copyOrAssign(const Board &b);
    void initBoard();

private:
    //store Piece idx of every board position
    int m_chessBoard[10][9]; 
    //store the Information  of 32 pieces
    Piece m_pieces[32]; 
};

extern Board g_board;



#endif // BOARD_H
