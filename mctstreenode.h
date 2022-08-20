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

public:
    //是红色还是黑子走棋
    PIECE_COLOR currentColor;
    PIECE_COLOR winner;
    //是否是终点
    bool isTerminal;
    //是否被完全扩展
    bool isFullyExpanded;
    //父节点
    MCTSTreeNode *parent;
    //被访问的次数
    int numVisited;
    //Ai获胜的次数
    int numAiWin;
    //当前棋局
    Board board;
    //子节点
    vector<MCTSTreeNode*> children;

    int visitedChildrenCnt;

    void isEnd();
};



vector<ChessMove> getAllMove(vector<vector<int>>& chessBoard, vector<Piece> pieces);

#endif // MCTSTREENODE_H
