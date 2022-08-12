#include "ai.h"

Ai::Ai(Board *_board, PIECE_COLOR _color): m_board(board), aiColor(_color), tree(nullptr){

}

Ai::～Ai() {
    m_board = nullptr;
    delete tree;
}