#include "piece.h"
#include "board.h"
#include <QDebug>

QString g_imagesSources[14] = {
    "../images/BLACK_GENERAL.gif",
    "../images/BLACK_ADVISOR.gif",
    "../images/BLACK_ELEPHANT.gif",
    "../images/BLACK_HORSE.gif",
    "../images/BLACK_CHARIOT.gif",
    "../images/BLACK_CANNON.gif",
    "../images/BLACK_SOLDIER.gif",

    "../images/RED_GENERAL.gif",
    "../images/RED_ADVISOR.gif",
    "../images/RED_ELEPHANT.gif",
    "../images/RED_HORSE.gif",
    "../images/RED_CHARIOT.gif",
    "../images/RED_CANNON.gif",
    "../images/RED_SOLDIER.gif",
};


InitialPos g_initialPos[32] = {
    {0, 0,  BLACK_CHARIOT,  canChariotMove,     getChariotMove},
    {0, 1,  BLACK_HORSE,    canHorseMove,       getHorseMove},
    {0, 2,  BLACK_ELEPHANT, canElephantMove,    getElephantMove},
    {0, 3,  BLACK_ADVISOR,  canAdvisorMove,     getAdvisorMove},
    {0, 4,  BLACK_GENERAL,  canGeneralMove,     getGeneralMove},
    {0, 5,  BLACK_ADVISOR,  canAdvisorMove,     getAdvisorMove},
    {0, 6,  BLACK_ELEPHANT, canElephantMove,    getElephantMove},
    {0, 7,  BLACK_HORSE,    canHorseMove,       getHorseMove},
    {0, 8,  BLACK_CHARIOT,  canChariotMove,     getChariotMove},
    {2, 1,  BLACK_CANNON,   canCannoMove,       getCannoMove},
    {2, 7,  BLACK_CANNON,   canCannoMove,       getCannoMove},
    {3, 0,  BLACK_SOLDIER,  canSoldierMove,     getSoldierMove},
    {3, 2,  BLACK_SOLDIER,  canSoldierMove,     getSoldierMove},
    {3, 4,  BLACK_SOLDIER,  canSoldierMove,     getSoldierMove},
    {3, 6,  BLACK_SOLDIER,  canSoldierMove,     getSoldierMove},
    {3, 8,  BLACK_SOLDIER,  canSoldierMove,     getSoldierMove},

    {9, 0,  RED_CHARIOT,    canChariotMove,     getChariotMove},
    {9, 1,  RED_HORSE,      canHorseMove,       getHorseMove},
    {9, 2,  RED_ELEPHANT,   canElephantMove,    getElephantMove},
    {9, 3,  RED_ADVISOR,    canAdvisorMove,     getAdvisorMove},
    {9, 4,  RED_GENERAL,    canGeneralMove,     getGeneralMove},
    {9, 5,  RED_ADVISOR,    canAdvisorMove,     getAdvisorMove},
    {9, 6,  RED_ELEPHANT,   canElephantMove,    getElephantMove},
    {9, 7,  RED_HORSE,      canHorseMove,       getHorseMove},
    {9, 8,  RED_CHARIOT,    canChariotMove,     getChariotMove},
    {7, 1,  RED_CANNON,     canCannoMove,       getCannoMove},
    {7, 7,  RED_CANNON,     canCannoMove,       getCannoMove},
    {6, 0,  RED_SOLDIER,    canSoldierMove,     getSoldierMove},
    {6, 2,  RED_SOLDIER,    canSoldierMove,     getSoldierMove},
    {6, 4,  RED_SOLDIER,    canSoldierMove,     getSoldierMove},
    {6, 6,  RED_SOLDIER,    canSoldierMove,     getSoldierMove},
    {6, 8,  RED_SOLDIER,    canSoldierMove,     getSoldierMove},
};

Piece::Piece() : canPieceMove(nullptr), allMoveMethod(nullptr),m_exist(true) , m_board(&g_board)
{

}

Piece::Piece(const Piece &piece) :m_type(piece.m_type), m_color(piece.m_color), m_exist(piece.m_exist),
                                    m_board(nullptr)
{

}

Piece::~Piece() {
    m_board = nullptr;
}

void Piece::Init(int id)
{
    //m_row = g_initialPos[id].row;
    //m_col = g_initialPos[id].col;
    m_type = g_initialPos[id].type;
    canPieceMove = g_initialPos[id].func;
    allMoveMethod = g_initialPos[id].func2;

    m_color = id <= 15? BLACK: RED;

}


bool canGeneralMove(pair<int, int> oldP, pair<int, int> newP, PIECE_COLOR color, Board *board)
{
    Q_UNUSED(board);
    int distance = abs(newP.first - oldP.first) + abs(newP.second - oldP.second);
    if(distance != 1)
        return false;

    if(color == BLACK && !(newP.first >= 0 && newP.first <= 2 && newP.second >= 3 && newP.second <= 5 ) )
        return false;

    if(color == RED && !(newP.first >= 7 && newP.first <= 9 && newP.second >= 3 && newP.second <= 5))
        return false;

    return true;
}

bool canAdvisorMove(pair<int, int> oldP, pair<int, int> newP, PIECE_COLOR color, Board *board)
{
    Q_UNUSED(board);

    if(abs(newP.first - oldP.first) != 1 || abs(newP.second - oldP.second) != 1)
        return false;

    if(color == BLACK && !(newP.first >= 0 && newP.first <= 2 && newP.second >= 3 && newP.second <= 5 ) )
        return false;

    if(color == RED && !(newP.first >= 7 && newP.first <= 9 && newP.second >= 3 && newP.second <= 5))
        return false;

    return true;
}

bool canElephantMove(pair<int, int> oldP, pair<int, int> newP, PIECE_COLOR color, Board *board)
{
    if(abs(newP.first - oldP.first) != 2 || abs(newP.second - oldP.second) != 2)
        return false;

    if(color == BLACK && !(newP.first >= 0 && newP.first <= 4 ) )
        return false;

    if(color == RED && !(newP.first >= 5 && newP.first <= 9))
        return false;

    int eyeY = (newP.first + oldP.first) / 2;
    int eyeX = (newP.second + oldP.second) / 2;

    if(board->getPieceType(eyeY, eyeX) != NO_PIECE)
        return false;

    return true;
}

bool canHorseMove(pair<int, int> oldP, pair<int, int> newP, PIECE_COLOR color, Board *board)
{
    Q_UNUSED(color);
    int gapY = abs(newP.first - oldP.first);
    int gapX = abs(newP.second - oldP.second);

    if( ! ((gapY == 1 && gapX == 2) || (gapY == 2 && gapX == 1)) )
        return false;

    int eyeY = 0;
    int eyeX = 0;

    if(gapX == 2)
    {
        eyeY = oldP.first;
        eyeX = (oldP.second + newP.second )/ 2;
    }
    else{
        eyeX = oldP.second;
        eyeY = (oldP.first + newP.first) / 2;
    }

    if(board->getPieceType(eyeY, eyeX) != NO_PIECE)
        return false;

    return true;
}

bool canChariotMove(pair<int, int> oldP, pair<int, int> newP, PIECE_COLOR color, Board *board)
{
    Q_UNUSED(color);

    if(oldP.first != newP.first && oldP.second != newP.second)
        return false;

    if(oldP.first == newP.first)
    {
        for(int c = oldP.second + 1; c < newP.second; c++)
        {
            if(board->getPieceType(oldP.first, c) != NO_PIECE)
                return false;
        }
    }
    else{
        for(int r = oldP.first + 1; r < newP.first; ++r)
        {
            if(board->getPieceType(r, oldP.second) != NO_PIECE)
                return false;
        }
    }
    return true;
}

bool canCannoMove(pair<int, int> oldP, pair<int, int> newP, PIECE_COLOR color, Board *board)
{
    Q_UNUSED(color);
    if(oldP.first != newP.first && oldP.second != newP.second)
        return false;

    int pieceCnt = 0;
    if(oldP.first == newP.first)
    {
        for(int c = std::min(oldP.second, newP.second) + 1; c < std::max(oldP.second,newP.second); c++)
        {
            if(board->getPieceType(oldP.first, c) != NO_PIECE)
                ++pieceCnt;
        }

    }
    else{
        for(int r = std::min(oldP.first, newP.first) + 1; r < std::max(oldP.first, newP.first); ++r)
        {
            if(board->getPieceType(r, oldP.second) != NO_PIECE)
                ++pieceCnt;
        }
    }

    if(pieceCnt > 1)
        return false;

    qDebug()<<"pieceCnt:"<<pieceCnt;
    PIECE_TYPE target = board->getPieceType(newP.first, newP.second) ;

    if((target == NO_PIECE && pieceCnt != 0) || (target != NO_PIECE && pieceCnt != 1))
        return false;

    return true;
}


bool canSoldierMove(pair<int, int> oldP, pair<int, int> newP, PIECE_COLOR color, Board *board)
{
    Q_UNUSED(board);
    int distance = abs(oldP.first - newP.first) + abs(oldP.second - newP.second);
    if(distance != 1)
        return false;

    if(color == BLACK && ( (newP.first < oldP.first) || (oldP.first <= 4 && newP.first - oldP.first != 1)))
    {
        return false;
    }

    if(color == RED && ((newP.first > oldP.first) || (oldP.first >= 5 && newP.first - oldP.first != -1) )  )
    {
        return false;
    }

    return true;
}





//no problem
void getGeneralMove(pair<int,int> oldP,  PIECE_COLOR color, Board* board, vector<ChessMove>& chessMove)
{
    auto left = pair<int, int>(oldP.first, oldP.second - 1);
    auto right = pair<int, int>(oldP.first, oldP.second + 1);
    auto top = pair<int, int>(oldP.first - 1, oldP.second);
    auto down = pair<int, int>(oldP.first + 1, oldP.second);
    //左
    if(left.second >= 3 && isEmptyOrEnemy(board, color, left)) {
        chessMove.push_back(ChessMove(oldP, left));
    }
    //右
    if(right.second <= 5 && isEmptyOrEnemy(board, color, right)) {
        chessMove.push_back(ChessMove(oldP, right));
    }

    //下
    if( ((color == RED && down.first <= 9) || (color == BLACK && down.first <= 2))
            && isEmptyOrEnemy(board, color, down)) {
        chessMove.push_back(ChessMove(oldP, down));
    }
    //上
    if( ((color == RED && top.first >= 7) || (color == BLACK && top.first >= 0))
            && isEmptyOrEnemy(board, color, top) ) {
        chessMove.push_back(ChessMove(oldP, top));
    }

}

//no problem
void getAdvisorMove(pair<int,int> oldP,  PIECE_COLOR color, Board* board, vector<ChessMove>& chessMove)
{
    auto leftTop = pair<int, int>(oldP.first - 1, oldP.second - 1);
    auto rightTop = pair<int, int>(oldP.first - 1, oldP.second + 1);
    auto leftDown = pair<int, int>(oldP.first + 1, oldP.second - 1);
    auto rightDown = pair<int, int>(oldP.first + 1, oldP.second + 1);
    //左上
    if( ((color == RED && leftTop.first >= 7) || (color == BLACK && leftTop.first >= 0) )
            && leftTop.second >= 3 && isEmptyOrEnemy(board, color, leftTop) ){
        chessMove.push_back(ChessMove(oldP, leftTop));
    }
    //右上
    if( ((color == RED && rightTop.first >= 7 ) || (color == BLACK && rightTop.first >= 0))
            && rightTop.second <= 5 && isEmptyOrEnemy(board, color, rightTop) ) {
        chessMove.push_back(ChessMove(oldP, rightTop));
    }
    //左下
    if( ((color == RED && leftDown.first <= 9) || (color == BLACK && leftDown.first <= 2))
            && leftDown.second >= 3 && isEmptyOrEnemy(board, color, leftDown)) {
        chessMove.push_back(ChessMove(oldP, leftDown));
    }
    //右下
    if( ((color == RED && rightDown.first <= 9) || (color == BLACK && rightDown.first <= 2))
            && rightDown.second <= 5 && isEmptyOrEnemy(board, color,rightDown)) {
        chessMove.push_back(ChessMove(oldP, rightDown));
    }

}

//no problem
void getElephantMove(pair<int,int> oldP,  PIECE_COLOR color, Board* board, vector<ChessMove>& chessMove)
{
    auto leftTop = pair<int, int>(oldP.first - 2, oldP.second - 2);
    auto rightTop = pair<int, int>(oldP.first - 2, oldP.second + 2);
    auto leftDown = pair<int, int>(oldP.first + 2, oldP.second - 2);
    auto rightDown = pair<int, int>(oldP.first + 2, oldP.second + 2);
    //左上
    if( ((color == RED && leftTop.first >= 5) || (color == BLACK && leftTop.first >= 0))
            && leftTop.second >= 0 && isEmptyOrEnemy(board, color, leftTop) ) {
        chessMove.push_back(ChessMove(oldP, leftTop));
    }
    //右上
    if( ((color == RED && rightTop.first >= 5) || (color == BLACK && rightTop.first >= 0))
            && rightTop.second <= 8 && isEmptyOrEnemy(board, color, rightTop) ) {
        chessMove.push_back(ChessMove(oldP, rightTop));
    }
    //左下
    if( ((color == RED && leftDown.first <= 9) || (color == BLACK && leftDown.first <= 4))
            && leftDown.second >= 0 && isEmptyOrEnemy(board, color, leftDown)) {
        chessMove.push_back(ChessMove(oldP, leftDown));
    }
    //右下
    if( ((color == RED && rightDown.first <= 9) || (color == BLACK && rightDown.first <= 4))
            && rightDown.second <= 8 && isEmptyOrEnemy(board, color, rightDown)) {
        chessMove.push_back(ChessMove(oldP, rightDown));
    }
}


void getHorseMove(pair<int,int> oldP,  PIECE_COLOR color, Board* board, vector<ChessMove>& chessMove)
{
    auto left1_top2 = pair<int, int>(oldP.first - 2, oldP.second - 1);
    auto left2_top1 = pair<int, int>(oldP.first - 1, oldP.second - 2);
    auto right1_top2 = pair<int, int>(oldP.first - 2, oldP.second + 1);
    auto right2_top1 = pair<int, int>(oldP.first - 1, oldP.second + 2);

    auto left1_down2 = pair<int, int>(oldP.first + 2, oldP.second - 1);
    auto left2_down1 = pair<int, int>(oldP.first + 1, oldP.second - 2);
    auto right1_down2 = pair<int, int>(oldP.first + 2, oldP.second + 1);
    auto right2_down1 = pair<int, int>(oldP.first + 1, oldP.second + 2);

    //left1_top2
    if(isOnBoard(left1_top2) && isEmptyOrEnemy(board, color, left1_top2) &&
            board->getPieceType(oldP.first - 1, oldP.second) == NO_PIECE)
        chessMove.push_back(ChessMove(oldP, left1_top2));

    //left2_top1
    if(isOnBoard(left2_top1) && isEmptyOrEnemy(board, color, left2_top1) &&
            board->getPieceType(oldP.first, oldP.second - 1) == NO_PIECE)
        chessMove.push_back(ChessMove(oldP, left2_top1));

    //right1_top2
    if(isOnBoard(right1_top2) && isEmptyOrEnemy(board, color, right1_top2) &&
            board->getPieceType(oldP.first + 1, oldP.second) == NO_PIECE)
        chessMove.push_back(ChessMove(oldP, right1_top2));

    //right2_top1
    if(isOnBoard(right2_top1) && isEmptyOrEnemy(board, color, right2_top1) &&
            board->getPieceType(oldP.first, oldP.second + 1) == NO_PIECE)
        chessMove.push_back(ChessMove(oldP, right2_top1));

    //left1_down2
    if(isOnBoard(left1_down2) && isEmptyOrEnemy(board, color, left1_down2) &&
            board->getPieceType(oldP.first + 1, oldP.second) == NO_PIECE)
        chessMove.push_back(ChessMove(oldP, left1_down2));

    //left2_down1
    if(isOnBoard(left2_down1) && isEmptyOrEnemy(board, color, left2_down1) &&
            board->getPieceType(oldP.first, oldP.second - 1) == NO_PIECE)
        chessMove.push_back(ChessMove(oldP, left2_down1));

    //right1_down2
    if(isOnBoard(right1_down2) && isEmptyOrEnemy(board, color, right1_down2) &&
            board->getPieceType(oldP.first + 1, oldP.second) == NO_PIECE)
        chessMove.push_back(ChessMove(oldP, right1_down2));

    //right2_down1
    if(isOnBoard(right2_down1) && isEmptyOrEnemy(board, color, right2_down1) &&
            board->getPieceType(oldP.first, oldP.second + 1) == NO_PIECE)
        chessMove.push_back(ChessMove(oldP, right2_down1));


}
void getChariotMove(pair<int,int> oldP,  PIECE_COLOR color, Board* board, vector<ChessMove>& chessMove)
{
    //往上走
    for(int r = oldP.first - 1; r >= 0; --r) {
        if(board->getPieceType(r, oldP.second) == NO_PIECE)
            chessMove.push_back(ChessMove(oldP, pair<int, int>{r, oldP.second}));
        else {
            if(board->getPieceColor(r, oldP.second) != color)
                chessMove.push_back(ChessMove(oldP, pair<int, int>{r, oldP.second}));
            break;
        }
    }

    //往下走
    for(int r = oldP.first + 1; r <= 9; ++r) {
        if(board->getPieceType(r, oldP.second) == NO_PIECE)
            chessMove.push_back(ChessMove(oldP, pair<int, int>{r, oldP.second}));
        else {
            if(board->getPieceColor(r, oldP.second) != color)
                chessMove.push_back(ChessMove(oldP, pair<int, int>{r, oldP.second}));
            break;
        }
    }

    //往左走
    for(int c = oldP.second - 1; c >= 0; --c) {
        if(board->getPieceType(oldP.first, c) == NO_PIECE)
            chessMove.push_back(ChessMove(oldP, pair<int, int>{oldP.first, c}));
        else {
            if(board->getPieceColor(oldP.first, c) != color)
                chessMove.push_back(ChessMove(oldP, pair<int,int>{oldP.first, c}));
            break;
        }
    }

    //往右走
    for(int c = oldP.second + 1; c <= 8; ++c) {
        if(board->getPieceType(oldP.first, c) == NO_PIECE)
            chessMove.push_back(ChessMove(oldP, pair<int, int>{oldP.first, c}));
        else {
            if(board->getPieceColor(oldP.first, c) != color)
                chessMove.push_back(ChessMove(oldP, pair<int,int>{oldP.first, c}));
            break;
        }
    }
}


void getCannoMove(pair<int,int> oldP,  PIECE_COLOR color, Board* board, vector<ChessMove>& chessMove)
{
    //往上走
    bool MidPiece = false;
    for(int r = oldP.first - 1; r >= 0; --r) {
        if(!MidPiece && board->getPieceType(r, oldP.second) == NO_PIECE)
            chessMove.push_back(ChessMove(oldP, pair<int, int>{r, oldP.second}));
        else {
            if(!MidPiece)
                MidPiece = true;
            else if(board->getPieceType(r, oldP.second) == NO_PIECE)
                continue;
            else if(board->getPieceColor(r, oldP.second) != color) {
                chessMove.push_back(ChessMove(oldP, pair<int, int>{r, oldP.second}));
                break;
            }
            else break;
        }
    }
    //往下走
    MidPiece = false;
    for(int r = oldP.first + 1; r <= 9; ++r) {
        if(!MidPiece && board->getPieceType(r, oldP.second) == NO_PIECE)
            chessMove.push_back(ChessMove(oldP, pair<int, int>{r, oldP.second}));
        else {
            if(!MidPiece)
                MidPiece = true;
            else if(board->getPieceType(r, oldP.second) == NO_PIECE)
                continue;
            else if(board->getPieceColor(r, oldP.second) != color) {
                chessMove.push_back(ChessMove(oldP, pair<int, int>{r, oldP.second}));
                break;
            }
            else break;
        }
    }
    //往左走
    MidPiece = false;
    for(int c = oldP.second - 1; c >= 0; --c) {
        if(!MidPiece && board->getPieceType(oldP.first, c) == NO_PIECE)
            chessMove.push_back(ChessMove(oldP, pair<int, int>{oldP.first, c}));
        else {
            if(!MidPiece)
                MidPiece = true;
            else if(board->getPieceType(oldP.first, c) == NO_PIECE)
                continue;
            else if(board->getPieceColor(oldP.first, c) != color) {
                chessMove.push_back(ChessMove(oldP, pair<int, int>{oldP.first, c}));
                break;
            }
            else break;
        }
    }
    //往右走
    MidPiece = false;
    for(int c = oldP.second + 1; c <= 8; --c) {
        if(!MidPiece && board->getPieceType(oldP.first, c) == NO_PIECE)
            chessMove.push_back(ChessMove(oldP, pair<int, int>{oldP.first, c}));
        else {
            if(!MidPiece)
                MidPiece = true;
            else if(board->getPieceType(oldP.first, c) == NO_PIECE)
                continue;
            else if(board->getPieceColor(oldP.first, c) != color) {
                chessMove.push_back(ChessMove(oldP, pair<int, int>{oldP.first, c}));
                break;
            }
            else break;
        }
    }

}


void getSoldierMove(pair<int,int> oldP,  PIECE_COLOR color, Board* board, vector<ChessMove>& chessMove){
    if ((color == BLACK && oldP.first > 4) || (color == RED && oldP.first < 5)) {
        //左
        auto left = pair<int, int>{oldP.first, oldP.second - 1};
        if(isEmptyOrEnemy(board, color, left)) {
            ChessMove move(oldP, left);
            chessMove.push_back(move);
        }
        //右
        auto right = pair<int, int>{oldP.first, oldP.second + 1};
        if((isEmptyOrEnemy(board, color, right))) {
            ChessMove move(oldP, right);
            chessMove.push_back(move);
        }
    }

    if (color == BLACK) {
        auto down = pair<int, int>{oldP.first + 1, oldP.second};
        if(isEmptyOrEnemy(board, color, down)) {
            ChessMove move(oldP, down);
            chessMove.push_back(move);
        }
        return ;
    }

    if (color == RED) {
        auto top = pair<int, int>{oldP.first - 1, oldP.second};
        if(isEmptyOrEnemy(board, color, top)) {
            ChessMove move(oldP, top);
            chessMove.push_back(move);
        }
        return ;
    }

}

bool isOnBoard(pair<int, int> p) {
    if (p.first < 0 || p.first > 9 || p.second < 0 || p.second > 8)
        return false;
    return true;
}

bool isEmptyOrEnemy(Board* board, PIECE_COLOR color, pair<int, int> pos) {
    return board->getPieceType(pos.first, pos.second) == NO_PIECE
            || board->getPieceColor(pos.first, pos.second) != color;
}




