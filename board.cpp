#include "board.h"
#include <QtDebug>

Board g_board;

/**
 * @brief Construct a new Board:: Board object
 * Should only be called once in GameController
 */
Board::Board()
{
    initBoard();
}

Board::Board(const Board &b)
{
    copyOrAssign(b);
}

Board &Board::operator=(const Board &b)
{
    copyOrAssign(b);
    return *this;
}

/**
 * @brief  Only be called in Copy Constructor and Copy Asssignment
 *
 * @param b
 */
void Board::copyOrAssign(const Board &b) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 9; ++j) {
            m_chessBoard[i][j] = b.m_chessBoard[i][j];
        }
    }

    for (int i = 0; i < 32; ++i) {
        m_pieces[i] = b.m_pieces[i];
        m_pieces[i].m_board = this;
    }
}

/**
 * @brief init the Board, called in constructor
 *
 */
void Board::initBoard() {
    // initial pieces
    for (int i = 0; i < 32; ++i) {
        m_pieces[i].Init(i);
    }

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 9; ++j) {
            m_chessBoard[i][j] = -1;
        }
    }

    for (int i = 0; i < 32; ++i) {
        m_chessBoard[g_initialPos[i].row][g_initialPos[i].col] = i;
    }
}

/**
 * @brief Whether the Board can move the piece from oldP to newP
 *
 * @param oldP Original position of the piece
 * @param newP Target position of the piece
 * @return true
 * @return false
 */
bool Board::canMove(const pair<int, int> &oldP, const pair<int, int> &newP) {
    Piece *pieceOld = &m_pieces[m_chessBoard[oldP.first][oldP.second]];
    if (getPieceID(newP.first, newP.second) == -1) {
        return pieceOld->canPieceMove(oldP, newP, pieceOld->getColor(), this);
    }

    Piece *pieceNew = &m_pieces[m_chessBoard[newP.first][newP.second]];

    // same Color, return false
    if (pieceNew->getType() != NO_PIECE && (pieceOld->getColor() == pieceNew->getColor())) {
        return false;
    }
    return pieceOld->canPieceMove(oldP, newP, pieceOld->getColor(), this);
}

/**
 * @brief Mover the Piece from oldP to newP
 * @param oldP
 * @param newP
 */
void Board::movePiece(const pair<int, int> &oldP, const pair<int, int> &newP) {
    // Piece on oldP
    PIECE_TYPE type = getPieceType(newP);

    // Destroy the target position pieces
    if (type != NO_PIECE) {
        int destroyedChessIdx = m_chessBoard[newP.first][newP.second];
        m_pieces[destroyedChessIdx].destroyPiece();
        m_chessBoard[newP.first][newP.second] = -1;
    }
    // move to target
    int movedChessIdx = m_chessBoard[oldP.first][oldP.second];
    setPieceID(newP.first, newP.second, movedChessIdx);
    setPieceID(oldP.first, oldP.second, -1);
}

/**
 * @brief Move the piece according to ChessMove
 * @param chessMove move method
 */
void Board::movePiece(const ChessMove &chessMove) {
    movePiece(chessMove.from, chessMove.to);
}
