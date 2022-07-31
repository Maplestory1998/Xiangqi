#include "mctstreenode.h"
#include <math.h>
#include <random>

MCTSTreeNode::MCTSTreeNode()
{

}

MCTSTreeNode* MCTSTreeNode::select() {
    double bestValue = 0.0;
    vector<MCTSTreeNode*> bestNodes;
    for (MCTSTreeNode *node  : children) {
        double nodeValue = static_cast<double>(node->numWin) / static_cast<double>(node->numVisited)
                            + explorationValue * sqrt(2.0 * log(numVisited) / node->numVisited);
        if (nodeValue > bestValue + eps) {
            bestValue = nodeValue;
            bestNodes.clear();
            bestNodes.push_back(node);
        } else if (abs(nodeValue - bestValue) < eps) {
            bestNodes.push_back(node);
        }
    }
    return randomChoice(bestNodes);
}


void MCTSTreeNode::backpropogate(int reward) {
    MCTSTreeNode* node = this;
    while(node != nullptr) {
        node->numVisited += 1;
        node->numWin += reward;
        node = node->parent;
    }
}


void MCTSTreeNode::init() {
    isTerminal = false;
    isFullyExpanded = false;
    //父节点
    parent = nullptr;
    //被访问的次数
    numVisited = 0;
    //获胜的次数
    numWin = 0;

}

MCTSTreeNode* MCTSTreeNode::randomChoice(vector<MCTSTreeNode*> nodes) {
    int idx = rand() % (nodes.size());
    return nodes[idx];
}

vector<ChessMove> getAllMove(vector<vector<int>>& chessBoard, vector<Piece> pieces) {

}
