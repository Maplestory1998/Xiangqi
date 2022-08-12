#ifndef AI_H
#define AI_H

#include <vector>
#include "board.h"
#include <mctstreenode.h>
#include "mctstree.h"
using namespace std;

class Ai
{
public:
    Ai(Board *_board, PIECE_COLOR _color);
    Ai::(const Ai &ai) = delete;
    Ai& operator=(const Ai &ai) = delete;
    ～Ai();


public:
    Board *m_board;

private:
    PIECE_COLOR aiColor;
    MCTSTree *tree;
};






#endif // AI_H
