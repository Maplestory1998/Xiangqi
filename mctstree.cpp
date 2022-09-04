#include "mctstree.h"
#include <time.h>
#include <QDebug>
#include <piece.h>
#include "evaluation.h"
#include <QApplication>



MCTSTree::MCTSTree(Board *_board, PIECE_COLOR color): root(new MCTSTreeNode(_board, color, nullptr)), aiColor(color) {
    
}

MCTSTree::~MCTSTree() {
    delete root;
}


MCTSTreeNode* MCTSTree::mctsSearch() {
    time_t start = time(nullptr);
    time_t end = time(nullptr);
    while(difftime(end, start) < 2.0) {
        MCTSTreeNode* leaf = traverse(root);
        int reward = rollout(leaf);
        backpropogate(leaf, reward);
        end = time(nullptr);
    }

    return mostEmplored(root);
}


int MCTSTree::rollout(MCTSTreeNode *node) {
    int layer = 3;
    while(!node->isTerminal && layer > 0) {
        node = rolloutPolicy(node);
        --layer;
    }
    if (node->isTerminal) {
        return node->winner == aiColor? 1 : 0;
    }

    PIECE_COLOR color = evalutationFunction(&node->board);
    return color == aiColor? 1 : 0;
}


MCTSTreeNode *MCTSTree::rolloutPolicy(MCTSTreeNode *node) {
    vector<ChessMove> move;
    while (move.size() == 0) {
        int idx = rand() % 32;
        while (node->board.getPiece(idx).isExist() == false || node->board.getPiece(idx).getColor() != node->currentColor) {
            idx = rand() % 32;
        }

        Piece p = node->board.getPiece(idx);
        p.allMoveMethod(p.getPos(), node->currentColor, &node->board, move);
    }

    int randIdx = rand()% move.size();
    MCTSTreeNode *next = new MCTSTreeNode(&node->board, node->currentColor == BLACK? RED : BLACK, &move[randIdx], node);
    node->children.push_back(next);

    return next;

}

MCTSTreeNode* MCTSTree::traverse(MCTSTreeNode* node) {
    while(node->isFullyExpanded) {
        node = bestChild(node);
    }
    if(node->isTerminal) {
        return node;
    }

    MCTSTreeNode *res = pickUnvisited(node);
    return res;
}

MCTSTreeNode* MCTSTree::pickUnvisited(MCTSTreeNode *node) {
    if (node->visitedChildrenCnt == 0) {
        generateChildren(node);
        MCTSTreeNode *res = randomChoice(node->children);
        return res;
    }

    vector<MCTSTreeNode*> choices;
    for (auto child: node->children ) {
        if(child->numVisited == 0) {
            choices.push_back(child);
        }
    }
    return randomChoice(choices);

}


MCTSTreeNode* MCTSTree::bestChild(MCTSTreeNode *node) {
    double bestValue = 0.0;
    vector<MCTSTreeNode*> bestNodes;
    for (MCTSTreeNode *child  : node->children) {
        if (child->numVisited == 0) {
            continue;
        }
        double nodeValue = 0.0;
        if (child->currentColor != aiColor) {
            nodeValue = static_cast<double>(child->numAiWin) / static_cast<double>(child->numVisited)
                                        + explorationValue * sqrt(2.0 * log(node->numVisited) / child->numVisited);
        } else {
            nodeValue = static_cast<double>(child->numVisited - child->numAiWin) /static_cast<double>(child->numVisited)
                                        + explorationValue * sqrt(2.0 * log(node->numVisited) / child->numVisited);
        }

        if (nodeValue > bestValue + eps) {
            bestValue = nodeValue;
            bestNodes.clear();
            bestNodes.push_back(child);
        } else if (abs(nodeValue - bestValue) < eps) {
            bestNodes.push_back(child);
        }
    }
    return randomChoice(bestNodes);
}


MCTSTreeNode* MCTSTree::mostEmplored(MCTSTreeNode* node) {
    MCTSTreeNode *res = node->children[0];
    for (auto child : node->children) {
        if (child->numVisited > res->numVisited) {
            res = child;
        }
    }
    return res;
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
        Piece p = node->board.getPiece(i);
        if (p.isExist() && p.getColor() == aiColor) {
            p.allMoveMethod(p.getPos(), p.getColor(), &node->board, chessMove);
        }
    }

    for(auto i : chessMove) {
        MCTSTreeNode *child = new MCTSTreeNode(&node->board, node->currentColor == RED? BLACK: RED, &i, node);
        node->children.push_back(child);
    }
}



MCTSTreeNode* MCTSTree::randomChoice(vector<MCTSTreeNode*> &nodes) {
    if (nodes.size() == 0) {
           return nullptr;
    }

    int idx = rand() % (nodes.size());
    return nodes[idx];
}

void MCTSTree::updateState(MCTSTreeNode *node) {
    if (++(node->visitedChildrenCnt) == node->children.size()) {
        node->isFullyExpanded = true;
    }
}
