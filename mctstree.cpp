#include "mctstree.h"
#include <time.h>
#include <QDebug>
#include <piece.h>
#include "evaluation.h"



MCTSTree::MCTSTree(Board *_board, PIECE_COLOR color): root(new MCTSTreeNode(_board, color, nullptr)), aiColor(color) {
    
}

MCTSTree::~MCTSTree() {
    delete root;
}


MCTSTreeNode* MCTSTree::mctsSearch()
{
    time_t begin = clock();
    time_t end = clock();
//    while(difftime(end, begin) <= 1) {
        end = clock();
        MCTSTreeNode* leaf = traverse(root);
        int reward = rollout(leaf);
        backpropogate(leaf, reward);
//    }

    MCTSTreeNode *res = bestChild(root);
    if (res == leaf)
        qDebug()<<"truetrue";
    else qDebug()<<"falsefalse";
    for (int i = 0; i < 10; ++i) {
        qDebug()<<"----------------";
        for (int j = 0; j < 9; ++j) {
            qDebug()<<res->board->getPieceType(i, j);
        }

    }
    return res;
}


int MCTSTree::rollout(MCTSTreeNode *node)
{
    int layer = 3;
    while(!node->isTerminal && layer > 0) {
        node = rolloutPolicy(node);
        --layer;
    }
    if (node->isTerminal)
        return node->winner == aiColor? 1 : 0;

    PIECE_COLOR color = evalutationFunction(node->board);
    return color == aiColor? 1 : 0;
}


MCTSTreeNode *MCTSTree::rolloutPolicy(MCTSTreeNode *node)
{
    vector<ChessMove> move;
    while (move.size() == 0) {
        int idx = rand() % 32;
        while (node->board->getPiece(idx).isExist() == false || node->board->getPiece(idx).getColor() != node->currentColor) {
            idx = rand() % 32;
        }

        Piece p = node->board->getPiece(idx);
        p.allMoveMethod(p.getPos(), node->currentColor, node->board, move);
    }

    int randIdx = rand()% move.size();
    MCTSTreeNode *next = new MCTSTreeNode(node->board, node->currentColor == BLACK? RED : BLACK, &move[randIdx], node);
    node->children.push_back(next);

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
        qDebug()<<node->children.size();
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
    qDebug()<<"children's size"<<node->children.size();
    for (MCTSTreeNode *child  : node->children) {
        if (child->numVisited == 0)
            continue;
        double nodeValue = 0.0;
        if (child->currentColor != aiColor) {
            nodeValue = static_cast<double>(child->numAiWin) / static_cast<double>(child->numVisited)
                                        + explorationValue * sqrt(2.0 * log(node->numVisited) / child->numVisited);
        } else
            nodeValue = static_cast<double>(child->numVisited - child->numAiWin) /static_cast<double>(child->numVisited)
                                        + explorationValue * sqrt(2.0 * log(node->numVisited) / child->numVisited);

        if (nodeValue > bestValue + eps) {
            bestValue = nodeValue;
            bestNodes.clear();
            bestNodes.push_back(child);
        } else if (abs(nodeValue - bestValue) < eps) {
            bestNodes.push_back(child);
        }
    }
    qDebug()<<"bestNode's size: "<<bestNodes.size();
    if(bestNodes.size() == 1) {
        qDebug()<<"sb";
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 9; ++j) {
                qDebug()<<bestNodes[0]->board->getPieceType(i, j);
            }
            qDebug()<<"----------------------------";
        }
    }
    return randomChoice(bestNodes);
}


void MCTSTree::backpropogate(MCTSTreeNode* node, int reward) {
    for (auto child : node->children) {
        delete child;
        child = nullptr;
    }
    node->children.clear();
    updateState(node->parent);
    
    while(node != nullptr) {
        node->numVisited += 1;
        node->numAiWin += reward;
        node = node->parent;
    }
}


void MCTSTree::generateChildren(MCTSTreeNode *node) {
    vector<ChessMove> chessMove;
    for (int i = 0; i < 32; ++i) {
        Piece p = node->board->getPiece(i);
        if (p.isExist() && p.getColor() == aiColor) {
            p.allMoveMethod(p.getPos(), p.getColor(), node->board, chessMove);
        }
    }

    for(auto i : chessMove) {
        MCTSTreeNode *child = new MCTSTreeNode(node->board, node->currentColor == RED? BLACK: RED, &i, node);
        node->children.push_back(child);
    }
}



MCTSTreeNode* MCTSTree::randomChoice(vector<MCTSTreeNode*> &nodes) {
    int idx = rand() % (nodes.size());
    return nodes[idx];
}



void MCTSTree::updateState(MCTSTreeNode *node) {
    if (++(node->visitedChildrenCnt) == node->children.size())
        node->isFullyExpanded = true;
}
