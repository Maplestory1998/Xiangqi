#ifndef MCTSTREE_H
#define MCTSTREE_H

#include "mctstreenode.h"
#include "board.h"

class MCTSTree
{
public:
    MCTSTree(Board *board, PIECE_COLOR _color);
    ~MCTSTree();
    

    MCTSTreeNode* mctsSearch();

    MCTSTreeNode* bestChild(MCTSTreeNode *node);

    void generateChildren(MCTSTreeNode *node);

    MCTSTreeNode* randomChoice(vector<MCTSTreeNode*> &nodes);

    void backpropogate(MCTSTreeNode* node, int reward);

    MCTSTreeNode* traverse(MCTSTreeNode* node);

    MCTSTreeNode* pickUnvisited(MCTSTreeNode *node);

    int rollout(MCTSTreeNode *node);

    MCTSTreeNode *rolloutPolicy(MCTSTreeNode *node);

    void updateState(MCTSTreeNode *node);

    MCTSTreeNode* mostEmplored(MCTSTreeNode* node);
public:
    MCTSTreeNode *root;

    PIECE_COLOR aiColor;
};

#endif // MCTSTREE_H
