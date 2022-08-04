#include "ai.h"

Ai::Ai(Board *_board, PIECE_COLOR _color): m_board(_board), aiColor(_color),
    tree(m_board, aiColor)
{

}
