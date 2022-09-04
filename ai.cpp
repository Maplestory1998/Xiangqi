#include "ai.h"
#include <QDebug>

Ai::Ai(Board *_board, PIECE_COLOR _color): m_board(_board), aiColor(_color), tree(nullptr) {

}

Ai::~Ai() {
    m_board = nullptr;
    delete tree;
}

/**
 * @brief Run the ai;
 * @param _aiColor 
 */
void Ai::run(PIECE_COLOR _aiColor, GameController *gameController) {
    tree = new MCTSTree(m_board, _aiColor);

    MCTSTreeNode* node = tree->mctsSearch();
    int idx = 0;
    for (int r = 0; r < 10; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (node->board.getPieceID(r, c) != m_board->getPieceID(r, c)) {
                ++idx;
                if (idx== 1) {
                    gameController->setCurPos(r, c);
                } else if(idx == 2) {
                    gameController->setChosePos(r, c);
                    break;
                }
            }
        }
    }
    *m_board = node->board;
    for (int i = 0; i < 32; ++i) {
        m_board->getPiece(i).setBoard(&g_board);
    }
    delete tree;
    tree = nullptr;
}
