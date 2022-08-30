#ifndef MCTSTREENODE_H
#define MCTSTREENODE_H

#include <vector>
#include <utility>
#include "piece.h"
#include "board.h"
using namespace std;

const double explorationValue = 1.0;
const double eps = 1e-6;


class MCTSTreeNode
{
public:
    MCTSTreeNode(Board *_board, PIECE_COLOR color, ChessMove *move, MCTSTreeNode *parent = nullptr);
    ~MCTSTreeNode();

    void isEnd();

public:
    //The player who moves in the turn
    PIECE_COLOR currentColor;
    PIECE_COLOR winner;
    //Is it a leaf node?
    bool isTerminal;
    //Whether it is fully extended
    bool isFullyExpanded;
    //Parent node
    MCTSTreeNode *parent;
    //The number of times the node was visited
    int numVisited;
    //The number of times Ai wins
    int numAiWin;
    //current game situation
    Board board;
    //children nodes
    vector<MCTSTreeNode*> children;
    //Number of child nodes that have been visited
    int visitedChildrenCnt;
};



vector<ChessMove> getAllMove(vector<vector<int>>& chessBoard, vector<Piece> pieces);

#endif // MCTSTREENODE_H
