#ifndef AI_H
#define AI_H

#include <vector>
#include "board.h"
#include <mctstreenode.h>
using namespace std;

class Ai
{
public:
    Ai(Board *_board);

    Board *m_board;
    MCTSTreeNode *root;

    void initialMCTS();

    void process();
};






#endif // AI_H
