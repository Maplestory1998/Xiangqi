#include "ai.h"

Ai::Ai(Board *_board): m_board(_board)
{

}


void Ai::initialMCTS() {
    root = new MCTSTreeNode();
    root->m_chessBoard.clear();
    root->m_chessBoard.resize(10, vector<int>(0, -1));
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 9; ++j) {
            root->m_chessBoard[i][j] = m_board->getPieceID(i, j);
        }
    }
}

void Ai::process(){
    initialMCTS();

}
