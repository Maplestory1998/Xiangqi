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

    //产生子节点
    void generateChildren(MCTSTreeNode *node);


    MCTSTreeNode* randomChoice(vector<MCTSTreeNode*> &nodes);

    //反向传播,update
    void backpropogate(MCTSTreeNode* node, int reward);

    MCTSTreeNode* traverse(MCTSTreeNode* node);

    //随机选择未被选择的节点
    MCTSTreeNode* pickUnvisited(MCTSTreeNode *node);

    int rollout(MCTSTreeNode *node);

    MCTSTreeNode *rolloutPolicy(MCTSTreeNode *node);

    void updateState(MCTSTreeNode *node);

public:
    //根节点
    MCTSTreeNode *root;

    //ai的颜色
    PIECE_COLOR aiColor;
};

#endif // MCTSTREE_H
