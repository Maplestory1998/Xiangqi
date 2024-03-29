#include "board.h"
#include <QtDebug>


Board g_board;

Board::Board()
{
    init();
}

Board::Board(Board &b)
{
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 9; ++j) {
            m_chessBoard[i][j] = b.m_chessBoard[i][j]; //store Piece idx of every board position
            m_pieceType[i][j] = b.m_pieceType[i][j];
        }
    }
    for(int i = 0; i < 32; ++i) {
        m_pieces[i] = b.m_pieces[i];
        m_pieces[i].m_board = nullptr;
    }
}


void Board::init()
{
    initBoard();
}


void Board::initBoard()
{
    //initial pieces
    for(int i = 0; i < 32; ++i)
    {
        m_pieces[i].Init(i);
    }


    for(int i = 0; i < 10; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            m_pieceType[i][j] = NO_PIECE;
            m_chessBoard[i][j] = -1;
        }
    }

    for(int i = 0; i < 32; ++i)
    {
        m_chessBoard[g_initialPos[i].row][g_initialPos[i].col] = i;
        m_pieceType[g_initialPos[i].row][g_initialPos[i].col] = m_pieces[i].getType();
    }

}


bool Board::canMove(pair<int, int> oldP, pair<int, int> newP)
{
    Piece *pieceOld = &m_pieces[m_chessBoard[oldP.first][oldP.second]];
    Piece *pieceNew = &m_pieces[m_chessBoard[newP.first][newP.second]];

    //若两个子颜色相同则跳出
    if(pieceNew->getType() != NO_PIECE && (pieceOld->getColor() == pieceNew->getColor()))
    {
        qDebug()<<"same side piece, cant move.";
        return false;
    }

    return pieceOld->canPieceMove(oldP, newP, pieceOld->getColor(), this);
}


void Board::movePiece(pair<int, int> oldP, pair<int, int> newP)
{
    //新位置的旧棋子
    PIECE_TYPE type = m_pieceType[newP.first][newP.second];

    //新位置有棋子
    //Destroy the target position pieces
    if(type != NO_PIECE)
    {
        int destroyedChessIdx = m_chessBoard[newP.first][newP.second];
        m_pieces[destroyedChessIdx].destroyPiece();
        setPieceType(newP.first, newP.second, NO_PIECE);
    }

    //move to target
    int movedChessIdx = m_chessBoard[oldP.first][oldP.second];
    setPieceID(newP.first, newP.second, movedChessIdx);
    setPieceType(newP.first, newP.second, m_pieceType[oldP.first][oldP.second]);

    setPieceID(oldP.first, oldP.second, -1);
    setPieceType(oldP.first, oldP.second, NO_PIECE);

}

void Board::movePiece(const ChessMove &chessMove) {
    movePiece(chessMove.from, chessMove.to);
}





