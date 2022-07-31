#ifndef MCTSTREENODE_H
#define MCTSTREENODE_H

#include <vector>
#include <QPair>
#include "piece.h"
using namespace std;

const double explorationValue = 1.0;
const double eps = 1e-6;


class MCTSTreeNode
{
public:
    MCTSTreeNode();

    //是否是终点
    bool isTerminal;
    //是否被完全扩展
    bool isFullyExpanded;
    //父节点
    MCTSTreeNode *parent;
    //被访问的次数
    int numVisited;
    //获胜的次数
    int numWin;
    vector<MCTSTreeNode*> children;

    //当前棋局
    vector<vector<int>> m_chessBoard;

    //选择
    MCTSTreeNode* select();

    void init();

    //扩展
    void expand();

    //反向传播
    void backpropogate(int reward);

private:
    MCTSTreeNode* randomChoice(vector<MCTSTreeNode*> nodes);
};

vector<ChessMove> getAllMove(vector<vector<int>>& chessBoard, vector<Piece> pieces);

#endif // MCTSTREENODE_H
