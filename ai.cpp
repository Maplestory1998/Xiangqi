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
void Ai::run(PIECE_COLOR _aiColor) {
    tree = new MCTSTree(m_board, _aiColor);

    MCTSTreeNode* node = tree->mctsSearch();
    *m_board = node->board;
    for (int i = 0; i < 32; ++i) {
        m_board->getPiece(i).setBoard(&g_board);
    }
    delete tree;
    tree = nullptr;
}
