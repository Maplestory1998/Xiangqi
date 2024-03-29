#include "mctstree.h"
#include <time.h>
#include <QDebug>
#include <piece.h>

MCTSTree::MCTSTree(Board *_board, PIECE_COLOR color): root(new MCTSTreeNode(_board, color, nullptr)), aiColor(color)
{

}

MCTSTreeNode* MCTSTree::mctsSearch()
{
    time_t begin = clock();
    time_t end = clock();
//    while(difftime(end, begin) <= 10000) {
//        end = clock();
        MCTSTreeNode* leaf = traverse(root);
        int reward = rollout(leaf);
        backpropogate(leaf, reward);
//    }
    return bestChild(root);
}


int MCTSTree::rollout(MCTSTreeNode *node)
{
    while(!node->isTerminal) {
        node = rolloutPolicy(node);
    }
    return node->winner == aiColor? 1 : 0;
}


MCTSTreeNode *MCTSTree::rolloutPolicy(MCTSTreeNode *node)
{
    int r = rand() % 10;
    int c = rand() % 9;
    while(node->board->getPieceType(r, c) == NO_PIECE && node->board->getPieceColor(r, c) != node->currentColor)
    {
        r = rand() % 10;
        c = rand() % 9;
    }

    int idx  = node->board->getPieceID(r, c);
    vector<ChessMove> move;
    node->board->getPiece(idx).allMoveMethod(pair<int,int>(r,c), node->currentColor, node->board, move );
    if(move.empty()) {
        node->isTerminal = true;
        node->winner = node->currentColor == RED?  BLACK: RED;
        return node;
    }
    int randIdx = rand() % move.size();
    MCTSTreeNode *next = new MCTSTreeNode(node->board, node->currentColor == BLACK? RED : BLACK, &move[randIdx], node);

    return next;

}

MCTSTreeNode* MCTSTree::traverse(MCTSTreeNode* node)
{
    while(node->isFullyExpanded)
        node = bestChild(node);
    if(node->isTerminal)
        return node;
    return pickUnvisited(node);
}

MCTSTreeNode* MCTSTree::pickUnvisited(MCTSTreeNode *node)
{
    if (node->numVisited == 0) {
        generateChildren(node);
        MCTSTreeNode *res = randomChoice(node->children);
        return res;
    }
    vector<MCTSTreeNode*> choices;
    for (auto child: node->children ) {
        if(child->numVisited == 0)
            choices.push_back(child);
    }
    return randomChoice(choices);

}


MCTSTreeNode* MCTSTree::bestChild(MCTSTreeNode *node) {
    double bestValue = 0.0;
    vector<MCTSTreeNode*> bestNodes;
    for (MCTSTreeNode *child  : node->children) {
        if (child->numVisited == 0)
            continue;
        double nodeValue = 0.0;
        if (node->currentColor != aiColor) {
            nodeValue = static_cast<double>(node->numAiWin) / static_cast<double>(node->numVisited)
                                        + explorationValue * sqrt(2.0 * log(node->numVisited) / child->numVisited);
        } else
            nodeValue = static_cast<double>(node->numVisited - node->numAiWin) /static_cast<double>(node->numVisited)
                                        + explorationValue * sqrt(2.0 * log(node->numVisited) / child->numVisited);

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


void MCTSTree::backpropogate(MCTSTreeNode* node, int reward) {
    while(node != nullptr) {
        node->numVisited += 1;
        node->numAiWin += reward;
        node = node->parent;
    }
}


void MCTSTree::generateChildren(MCTSTreeNode *node) {
//    //存储每个位置的棋子id
//    int m_chessBoard[10][9]; //store Piece idx of every board position
//    //存储每个位置的棋子类型
//    PIECE_TYPE m_pieceType[10][9];
//    //存储每个棋子的位置
//    Piece m_pieces[32];   //store the position info of 32
    vector<ChessMove> chessMove;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 9; ++j) {
            int idx = node->board->getPieceID(i, j);
            if (idx != -1)
            {
                node->board->getPiece(idx).allMoveMethod(pair<int,int>(i, j),node->board->getPieceColor(i, j), node->board, chessMove);
            }
        }
    }

    for(auto i : chessMove) {
        MCTSTreeNode *child = new MCTSTreeNode(node->board, node->currentColor == RED? BLACK: RED, &i, node);
        node->children.push_back(child);
    }
}



MCTSTreeNode* MCTSTree::randomChoice(vector<MCTSTreeNode*> nodes) {
    int idx = rand() % (nodes.size());
    return nodes[idx];
}
