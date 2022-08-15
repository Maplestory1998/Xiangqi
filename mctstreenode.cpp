#include "mctstreenode.h"
#include <math.h>
#include <random>

MCTSTreeNode::MCTSTreeNode(Board* _board, PIECE_COLOR color, ChessMove *move, MCTSTreeNode *_parent):
     isTerminal(false), currentColor(color), board(*_board),
    isFullyExpanded(false), parent(_parent), numVisited(0), numAiWin(0), visitedChildrenCnt(0)
{
    if(move != nullptr) {
        board.movePiece(*move);
    }

    isEnd();
}

MCTSTreeNode::~MCTSTreeNode() {
    for (auto child : children) {
        delete child;
        child = nullptr;
    }
    children.clear();
}


void MCTSTreeNode::isEnd()
{
    //BLACK general
    if(!board.getPiece(4).isExist()){
        isTerminal = true;
        winner = RED;
    }
    if(!board.getPiece(20).isExist()){
        isTerminal = true;
        winner = BLACK;
    }
}
