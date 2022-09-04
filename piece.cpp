#include "piece.h"
#include "board.h"
#include <QDebug>

//Piece image Source
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

//The information for board pieces initial
InitialPos g_initialPos[32] = {
    {0, 0,  BLACK_CHARIOT,  canChariotMove,     getChariotMove,     getChariotMoveMethodsCnt,   200,    1, chariotPosValue,   17},
    {0, 1,  BLACK_HORSE,    canHorseMove,       getHorseMove,       getHorseMoveMethodsCnt,     100,    3, horsePosValue,   8},
    {0, 2,  BLACK_ELEPHANT, canElephantMove,    getElephantMove,    getElephantMoveMethodsCnt,  50,     1, elephantPosValue,   4},
    {0, 3,  BLACK_ADVISOR,  canAdvisorMove,     getAdvisorMove,     getAdvisorMoveMethodsCnt,   50,     1, advisorPosValue,  4},
    {0, 4,  BLACK_GENERAL,  canGeneralMove,     getGeneralMove,     getGeneralMoveMethodsCnt,   3000,   1, generalPosValue, 4},
    {0, 5,  BLACK_ADVISOR,  canAdvisorMove,     getAdvisorMove,     getAdvisorMoveMethodsCnt,   50,     1, advisorPosValue,  4},
    {0, 6,  BLACK_ELEPHANT, canElephantMove,    getElephantMove,    getElephantMoveMethodsCnt,  50,     1, elephantPosValue,    4},
    {0, 7,  BLACK_HORSE,    canHorseMove,       getHorseMove,       getHorseMoveMethodsCnt,     100,    1, horsePosValue,  8},
    {0, 8,  BLACK_CHARIOT,  canChariotMove,     getChariotMove,     getChariotMoveMethodsCnt,   200,    1, chariotPosValue,  17},
    {2, 1,  BLACK_CANNON,   canCannoMove,       getCannoMove,       getCannoMoveMethodsCnt,     100,    1, cannoPosValue,  17},
    {2, 7,  BLACK_CANNON,   canCannoMove,       getCannoMove,       getCannoMoveMethodsCnt,     100,    1, cannoPosValue,   17},
    {3, 0,  BLACK_SOLDIER,  canSoldierMove,     getSoldierMove,     getSoldierMoveMethodsCnt,   25,     1, soldierPosValue,  3},
    {3, 2,  BLACK_SOLDIER,  canSoldierMove,     getSoldierMove,     getSoldierMoveMethodsCnt,   25,     1, soldierPosValue,  3},
    {3, 4,  BLACK_SOLDIER,  canSoldierMove,     getSoldierMove,     getSoldierMoveMethodsCnt,   25,     1, soldierPosValue,  3},
    {3, 6,  BLACK_SOLDIER,  canSoldierMove,     getSoldierMove,     getSoldierMoveMethodsCnt,   25,     1, soldierPosValue,  3},
    {3, 8,  BLACK_SOLDIER,  canSoldierMove,     getSoldierMove,     getSoldierMoveMethodsCnt,   25,     1, soldierPosValue,  3},

    {9, 0,  RED_CHARIOT,    canChariotMove,     getChariotMove,     getChariotMoveMethodsCnt,   200,    1, chariotPosValue,  17},
    {9, 1,  RED_HORSE,      canHorseMove,       getHorseMove,       getHorseMoveMethodsCnt,     100,    1, horsePosValue,  8},
    {9, 2,  RED_ELEPHANT,   canElephantMove,    getElephantMove,    getElephantMoveMethodsCnt,  50,     1, elephantPosValue,    4},
    {9, 3,  RED_ADVISOR,    canAdvisorMove,     getAdvisorMove,     getAdvisorMoveMethodsCnt,   50,     1, advisorPosValue,  4},
    {9, 4,  RED_GENERAL,    canGeneralMove,     getGeneralMove,     getGeneralMoveMethodsCnt,   3000,   1, generalPosValue,  4},
    {9, 5,  RED_ADVISOR,    canAdvisorMove,     getAdvisorMove,     getAdvisorMoveMethodsCnt,   50,     1, advisorPosValue,  4},
    {9, 6,  RED_ELEPHANT,   canElephantMove,    getElephantMove,    getElephantMoveMethodsCnt,  50,     1, elephantPosValue,    4},
    {9, 7,  RED_HORSE,      canHorseMove,       getHorseMove,       getHorseMoveMethodsCnt,     100,    1, horsePosValue, 8},
    {9, 8,  RED_CHARIOT,    canChariotMove,     getChariotMove,     getChariotMoveMethodsCnt,   200,    1, chariotPosValue,  17},
    {7, 1,  RED_CANNON,     canCannoMove,       getCannoMove,       getCannoMoveMethodsCnt,     100,    1, cannoPosValue,  17},
    {7, 7,  RED_CANNON,     canCannoMove,       getCannoMove,       getCannoMoveMethodsCnt,     100,    1, cannoPosValue,  17},
    {6, 0,  RED_SOLDIER,    canSoldierMove,     getSoldierMove,     getSoldierMoveMethodsCnt,   25,     1, soldierPosValue,  3},
    {6, 2,  RED_SOLDIER,    canSoldierMove,     getSoldierMove,     getSoldierMoveMethodsCnt,   25,     1, soldierPosValue,  3},
    {6, 4,  RED_SOLDIER,    canSoldierMove,     getSoldierMove,     getSoldierMoveMethodsCnt,   25,     1, soldierPosValue,  3},
    {6, 6,  RED_SOLDIER,    canSoldierMove,     getSoldierMove,     getSoldierMoveMethodsCnt,   25,     1, soldierPosValue,  3},
    {6, 8,  RED_SOLDIER,    canSoldierMove,     getSoldierMove,     getSoldierMoveMethodsCnt,   25,     1, soldierPosValue,  3},
};

Piece::Piece() : canPieceMove(nullptr), allMoveMethod(nullptr),m_exist(true) , m_board(&g_board) {

}

Piece::Piece(const Piece &piece) :m_type(piece.m_type), m_exist(piece.m_exist), value(piece.value), flexibilityFactor(piece.flexibilityFactor),
                                    m_board(nullptr), canPieceMove(piece.canPieceMove), allMoveMethod(piece.allMoveMethod), pos(piece.pos),
                                    getMoveMethodCnt(piece.getMoveMethodCnt),posEvalutaion(piece.posEvalutaion), maxMoveMethod(piece.maxMoveMethod) {

}

Piece& Piece::operator=(const Piece& p) {
    m_board = nullptr;
    pos = p.pos;
    m_type = p.m_type;
    m_exist = p.m_exist;
    posEvalutaion = p.posEvalutaion;
    value = p.value;
    flexibilityFactor = p.flexibilityFactor;
    maxMoveMethod = p.maxMoveMethod;

    canPieceMove = p.canPieceMove;
    allMoveMethod = p.allMoveMethod;
    getMoveMethodCnt = p.getMoveMethodCnt;

    return *this;
}

Piece::~Piece() {
    m_board = nullptr;
}

void Piece::Init(int id) {
    pos = {g_initialPos[id].row, g_initialPos[id].col};

    m_type = g_initialPos[id].type;
    canPieceMove = g_initialPos[id].func;
    allMoveMethod = g_initialPos[id].func2;
    getMoveMethodCnt = g_initialPos[id].func3;
    value = g_initialPos[id].value;
    maxMoveMethod = g_initialPos[id].maxMoveMethod;
    posEvalutaion = g_initialPos[id].posEvalutaion;
    flexibilityFactor = g_initialPos[id].flexibilityFactor;
}

/**
 * @brief Determine whether the piece can move from oldP to newP
 * 
 * @param oldP the old postision of the piece 
 * @param newP the new position of the piece
 * @param color
 * @param board 
 * @return true: the piece can move from oldP to newP
 * @return false can't move
 */
bool canGeneralMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board) {
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

bool canAdvisorMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board) {
    Q_UNUSED(board);

    if(abs(newP.first - oldP.first) != 1 || abs(newP.second - oldP.second) != 1)
        return false;

    if(color == BLACK && !(newP.first >= 0 && newP.first <= 2 && newP.second >= 3 && newP.second <= 5 ) )
        return false;

    if(color == RED && !(newP.first >= 7 && newP.first <= 9 && newP.second >= 3 && newP.second <= 5))
        return false;

    return true;
}

bool canElephantMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board) {
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

bool canHorseMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board) {
    Q_UNUSED(color);
    int gapY = abs(newP.first - oldP.first);
    int gapX = abs(newP.second - oldP.second);

    if( ! ((gapY == 1 && gapX == 2) || (gapY == 2 && gapX == 1)) )
        return false;

    int eyeY = 0;
    int eyeX = 0;

    if(gapX == 2) {
        eyeY = oldP.first;
        eyeX = (oldP.second + newP.second )/ 2;
    } else {
        eyeX = oldP.second;
        eyeY = (oldP.first + newP.first) / 2;
    }

    if(board->getPieceType(eyeY, eyeX) != NO_PIECE)
        return false;

    return true;
}

bool canChariotMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board) {
    Q_UNUSED(color);
    if(oldP.first != newP.first && oldP.second != newP.second)
        return false;

    if(oldP.first == newP.first) {
        for(int c = oldP.second + 1; c < newP.second; c++) {
            if(board->getPieceType(oldP.first, c) != NO_PIECE)
                return false;
        }
    } else{
        for(int r = oldP.first + 1; r < newP.first; ++r) {
            if(board->getPieceType(r, oldP.second) != NO_PIECE)
                return false;
        }
    }
    return true;
}

bool canCannoMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board) {
    Q_UNUSED(color);
    if(oldP.first != newP.first && oldP.second != newP.second)
        return false;

    int pieceCnt = 0;
    if(oldP.first == newP.first) {
        for(int c = std::min(oldP.second, newP.second) + 1; c < std::max(oldP.second,newP.second); c++) {
            if(board->getPieceType(oldP.first, c) != NO_PIECE)
                ++pieceCnt;
        }

    } else {
        for(int r = std::min(oldP.first, newP.first) + 1; r < std::max(oldP.first, newP.first); ++r) {
            if(board->getPieceType(r, oldP.second) != NO_PIECE)
                ++pieceCnt;
        }
    }

    if(pieceCnt > 1)
        return false;

    PIECE_TYPE target = board->getPieceType(newP.first, newP.second) ;
    if((target == NO_PIECE && pieceCnt != 0) || (target != NO_PIECE && pieceCnt != 1))
        return false;

    return true;
}


bool canSoldierMove(const pair<int, int> &oldP, const pair<int, int> &newP, PIECE_COLOR color, Board *board) {
    Q_UNUSED(board);
    int distance = abs(oldP.first - newP.first) + abs(oldP.second - newP.second);
    if(distance != 1)
        return false;

    if(color == BLACK && ( (newP.first < oldP.first) || (oldP.first <= 4 && newP.first - oldP.first != 1))) {
        return false;
    }

    if(color == RED && ((newP.first > oldP.first) || (oldP.first >= 5 && newP.first - oldP.first != -1) )  ) {
        return false;
    }

    return true;
}


/**
 * @brief Get the General Move Methods
 * 
 * @param oldP the old Position of the piece 
 * @param color the color of the piece 
 * @param board 
 * @param chessMove store the move methods of the piece
 */
void getGeneralMove(const pair<int, int> &oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove) {
    auto left = pair<int, int>(oldP.first, oldP.second - 1);
    auto right = pair<int, int>(oldP.first, oldP.second + 1);
    auto top = pair<int, int>(oldP.first - 1, oldP.second);
    auto down = pair<int, int>(oldP.first + 1, oldP.second);
    //left
    if(left.second >= 3 && isEmptyOrEnemy(board, color, left)) {
        chessMove.push_back(ChessMove(oldP, left));
    }
    //right
    if(right.second <= 5 && isEmptyOrEnemy(board, color, right)) {
        chessMove.push_back(ChessMove(oldP, right));
    }

    //down
    if( ((color == RED && down.first <= 9) || (color == BLACK && down.first <= 2))
            && isEmptyOrEnemy(board, color, down)) {
        chessMove.push_back(ChessMove(oldP, down));
    }
    //top
    if( ((color == RED && top.first >= 7) || (color == BLACK && top.first >= 0))
            && isEmptyOrEnemy(board, color, top) ) {
        chessMove.push_back(ChessMove(oldP, top));
    }

}

/**
 * @brief Get the Advisor Move Methods
 * 
 * @param oldP the old Position of the piece 
 * @param color the color of the piece 
 * @param board 
 * @param chessMove store the move methods of the piece
 */
void getAdvisorMove(const pair<int, int> &oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove) {
    auto leftTop = pair<int, int>(oldP.first - 1, oldP.second - 1);
    auto rightTop = pair<int, int>(oldP.first - 1, oldP.second + 1);
    auto leftDown = pair<int, int>(oldP.first + 1, oldP.second - 1);
    auto rightDown = pair<int, int>(oldP.first + 1, oldP.second + 1);
    //left top
    if( ((color == RED && leftTop.first >= 7) || (color == BLACK && leftTop.first >= 0) )
            && leftTop.second >= 3 && isEmptyOrEnemy(board, color, leftTop) ){
        chessMove.push_back(ChessMove(oldP, leftTop));
    }
    //right top
    if( ((color == RED && rightTop.first >= 7 ) || (color == BLACK && rightTop.first >= 0))
            && rightTop.second <= 5 && isEmptyOrEnemy(board, color, rightTop) ) {
        chessMove.push_back(ChessMove(oldP, rightTop));
    }
    //left down
    if( ((color == RED && leftDown.first <= 9) || (color == BLACK && leftDown.first <= 2))
            && leftDown.second >= 3 && isEmptyOrEnemy(board, color, leftDown)) {
        chessMove.push_back(ChessMove(oldP, leftDown));
    }
    //right down
    if( ((color == RED && rightDown.first <= 9) || (color == BLACK && rightDown.first <= 2))
            && rightDown.second <= 5 && isEmptyOrEnemy(board, color,rightDown)) {
        chessMove.push_back(ChessMove(oldP, rightDown));
    }

}

/**
 * @brief Get the Elephant Move Methods
 * 
 * @param oldP the old Position of the piece 
 * @param color the color of the piece 
 * @param board 
 * @param chessMove store the move methods of the piece
 */
void getElephantMove(const pair<int, int> &oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove) {
    auto leftTop = pair<int, int>(oldP.first - 2, oldP.second - 2);
    auto rightTop = pair<int, int>(oldP.first - 2, oldP.second + 2);
    auto leftDown = pair<int, int>(oldP.first + 2, oldP.second - 2);
    auto rightDown = pair<int, int>(oldP.first + 2, oldP.second + 2);
    //left top
    if( ((color == RED && leftTop.first >= 5) || (color == BLACK && leftTop.first >= 0))
            && leftTop.second >= 0 && isEmptyOrEnemy(board, color, leftTop) ) {
        chessMove.push_back(ChessMove(oldP, leftTop));
    }
    //right top
    if( ((color == RED && rightTop.first >= 5) || (color == BLACK && rightTop.first >= 0))
            && rightTop.second <= 8 && isEmptyOrEnemy(board, color, rightTop) ) {
        chessMove.push_back(ChessMove(oldP, rightTop));
    }
    //left down
    if( ((color == RED && leftDown.first <= 9) || (color == BLACK && leftDown.first <= 4))
            && leftDown.second >= 0 && isEmptyOrEnemy(board, color, leftDown)) {
        chessMove.push_back(ChessMove(oldP, leftDown));
    }
    //right down
    if( ((color == RED && rightDown.first <= 9) || (color == BLACK && rightDown.first <= 4))
            && rightDown.second <= 8 && isEmptyOrEnemy(board, color, rightDown)) {
        chessMove.push_back(ChessMove(oldP, rightDown));
    }
}


/**
 * @brief Get the Horse Move Methods
 * 
 * @param oldP the old Position of the piece 
 * @param color the color of the piece 
 * @param board 
 * @param chessMove store the move methods of the piece
 */
void getHorseMove(const pair<int, int> &oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove) {
    //leftx_topy  move x step to left and y to top
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

/**
 * @brief Get the Chariot Move Methods
 * 
 * @param oldP the old Position of the piece 
 * @param color the color of the piece 
 * @param board 
 * @param chessMove store the move methods of the piece
 */
void getChariotMove(const pair<int, int> &oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove) {
    //top
    for(int r = oldP.first - 1; r >= 0; --r) {
        if(board->getPieceType(r, oldP.second) == NO_PIECE) {
            chessMove.push_back(ChessMove(oldP, pair<int, int>{r, oldP.second}));
        } else {
            if(board->getPieceColor(r, oldP.second) != color) {
                chessMove.push_back(ChessMove(oldP, pair<int, int>{r, oldP.second}));
            }
            break;
        }
    }

    //down
    for(int r = oldP.first + 1; r <= 9; ++r) {
        if(board->getPieceType(r, oldP.second) == NO_PIECE) {
            chessMove.push_back(ChessMove(oldP, pair<int, int>{r, oldP.second}));
        } else {
            if(board->getPieceColor(r, oldP.second) != color) {
                chessMove.push_back(ChessMove(oldP, pair<int, int>{r, oldP.second}));
            }
            break;
        }
    }

    //left
    for(int c = oldP.second - 1; c >= 0; --c) {
        if(board->getPieceType(oldP.first, c) == NO_PIECE) {
            chessMove.push_back(ChessMove(oldP, pair<int, int>{oldP.first, c}));
        } else {
            if(board->getPieceColor(oldP.first, c) != color) {
                chessMove.push_back(ChessMove(oldP, pair<int,int>{oldP.first, c}));
            }
            break;
        }
    }

    //right
    for(int c = oldP.second + 1; c <= 8; ++c) {
        if(board->getPieceType(oldP.first, c) == NO_PIECE) {
            chessMove.push_back(ChessMove(oldP, pair<int, int>{oldP.first, c}));
        } else {
            if(board->getPieceColor(oldP.first, c) != color) {
                chessMove.push_back(ChessMove(oldP, pair<int,int>{oldP.first, c}));
            }
            break;
        }
    }
}

/**
 * @brief Get the Canno Move Methods
 * 
 * @param oldP the old Position of the piece 
 * @param color the color of the piece 
 * @param board 
 * @param chessMove store the move methods of the piece
 */
void getCannoMove(const pair<int, int> &oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove) {
    //top
    bool MidPiece = false;
    for(int r = oldP.first - 1; r >= 0; --r) {
        if(!MidPiece && board->getPieceType(r, oldP.second) == NO_PIECE) {
            chessMove.push_back(ChessMove(oldP, pair<int, int>{r, oldP.second}));
        } else {
            if(!MidPiece) {
                MidPiece = true;
            } else if(board->getPieceType(r, oldP.second) == NO_PIECE) {
                continue;
            } else if(board->getPieceColor(r, oldP.second) != color) {
                chessMove.push_back(ChessMove(oldP, pair<int, int>{r, oldP.second}));
                break;
            }
            else break;
        }
    }

    //down
    MidPiece = false;
    for(int r = oldP.first + 1; r <= 9; ++r) {
        if(!MidPiece && board->getPieceType(r, oldP.second) == NO_PIECE) {
            chessMove.push_back(ChessMove(oldP, pair<int, int>{r, oldP.second}));
        } else {
            if(!MidPiece) {
                MidPiece = true;
            } else if(board->getPieceType(r, oldP.second) == NO_PIECE) {
                continue;
            } else if(board->getPieceColor(r, oldP.second) != color) {
                chessMove.push_back(ChessMove(oldP, pair<int, int>{r, oldP.second}));
                break;
            }
            else break;
        }
    }

    //left
    MidPiece = false;
    for(int c = oldP.second - 1; c >= 0; --c) {
        if(!MidPiece && board->getPieceType(oldP.first, c) == NO_PIECE) {
            chessMove.push_back(ChessMove(oldP, pair<int, int>{oldP.first, c}));
        } else {
            if(!MidPiece) {
                MidPiece = true;
            } else if(board->getPieceType(oldP.first, c) == NO_PIECE) {
                continue;
            } else if(board->getPieceColor(oldP.first, c) != color) {
                chessMove.push_back(ChessMove(oldP, pair<int, int>{oldP.first, c}));
                break;
            }
            else break;
        }
    }

    //right
    MidPiece = false;
    for(int c = oldP.second + 1; c <= 8; ++c) {
        if(!MidPiece && board->getPieceType(oldP.first, c) == NO_PIECE) {
            chessMove.push_back(ChessMove(oldP, pair<int, int>{oldP.first, c}));
        } else {
            if(!MidPiece) {
                MidPiece = true;
            } else if(board->getPieceType(oldP.first, c) == NO_PIECE) {
                continue;
            } else if(board->getPieceColor(oldP.first, c) != color) {
                chessMove.push_back(ChessMove(oldP, pair<int, int>{oldP.first, c}));
                break;
            }
            else break;
        }
    }

}

/**
 * @brief Get the Soldier Move Methods
 * 
 * @param oldP the old Position of the piece 
 * @param color the color of the piece 
 * @param board 
 * @param chessMove store the move methods of the piece
 */
void getSoldierMove(const pair<int, int> &oldP,  PIECE_COLOR color, Board *board, vector<ChessMove>& chessMove){
    if ((color == BLACK && oldP.first > 4) || (color == RED && oldP.first < 5)) {
        //left
        auto left = pair<int, int>{oldP.first, oldP.second - 1};
        if(isEmptyOrEnemy(board, color, left)) {
            ChessMove move(oldP, left);
            chessMove.push_back(move);
        }
        //right
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


int getGeneralMoveMethodsCnt(const pair<int,int> &oldP, PIECE_COLOR color, Board *board) {
    int res = 0;
    auto left = pair<int, int>(oldP.first, oldP.second - 1);
    auto right = pair<int, int>(oldP.first, oldP.second + 1);
    auto top = pair<int, int>(oldP.first - 1, oldP.second);
    auto down = pair<int, int>(oldP.first + 1, oldP.second);
    //left
    if(left.second >= 3 && isEmptyOrEnemy(board, color, left)) {
        ++res;
    }
    //right
    if(right.second <= 5 && isEmptyOrEnemy(board, color, right)) {
        ++res;
    }

    //down
    if( ((color == RED && down.first <= 9) || (color == BLACK && down.first <= 2))
            && isEmptyOrEnemy(board, color, down)) {
        ++res;
    }
    //top
    if( ((color == RED && top.first >= 7) || (color == BLACK && top.first >= 0))
            && isEmptyOrEnemy(board, color, top) ) {
        ++res;
    }
    return res;
}

int getAdvisorMoveMethodsCnt(const pair<int,int> &oldP, PIECE_COLOR color, Board *board) {
    int res = 0;
    auto leftTop = pair<int, int>(oldP.first - 1, oldP.second - 1);
    auto rightTop = pair<int, int>(oldP.first - 1, oldP.second + 1);
    auto leftDown = pair<int, int>(oldP.first + 1, oldP.second - 1);
    auto rightDown = pair<int, int>(oldP.first + 1, oldP.second + 1);
    //left top
    if( ((color == RED && leftTop.first >= 7) || (color == BLACK && leftTop.first >= 0) )
            && leftTop.second >= 3 && isEmptyOrEnemy(board, color, leftTop) ){
        ++res;
    }
    //right top
    if( ((color == RED && rightTop.first >= 7 ) || (color == BLACK && rightTop.first >= 0))
            && rightTop.second <= 5 && isEmptyOrEnemy(board, color, rightTop) ) {
        ++res;
    }
    //left down
    if( ((color == RED && leftDown.first <= 9) || (color == BLACK && leftDown.first <= 2))
            && leftDown.second >= 3 && isEmptyOrEnemy(board, color, leftDown)) {
        ++res;
    }
    //right down
    if( ((color == RED && rightDown.first <= 9) || (color == BLACK && rightDown.first <= 2))
            && rightDown.second <= 5 && isEmptyOrEnemy(board, color,rightDown)) {
        ++res;
    }
    return res;
}


int getElephantMoveMethodsCnt(const pair<int,int> &oldP, PIECE_COLOR color, Board *board) {
    int res = 0;
    auto leftTop = pair<int, int>(oldP.first - 2, oldP.second - 2);
    auto rightTop = pair<int, int>(oldP.first - 2, oldP.second + 2);
    auto leftDown = pair<int, int>(oldP.first + 2, oldP.second - 2);
    auto rightDown = pair<int, int>(oldP.first + 2, oldP.second + 2);
    //left top
    if( ((color == RED && leftTop.first >= 5) || (color == BLACK && leftTop.first >= 0))
            && leftTop.second >= 0 && isEmptyOrEnemy(board, color, leftTop) ) {
        ++res;
    }
    //right top
    if( ((color == RED && rightTop.first >= 5) || (color == BLACK && rightTop.first >= 0))
            && rightTop.second <= 8 && isEmptyOrEnemy(board, color, rightTop) ) {
        ++res;
    }
    //left down
    if( ((color == RED && leftDown.first <= 9) || (color == BLACK && leftDown.first <= 4))
            && leftDown.second >= 0 && isEmptyOrEnemy(board, color, leftDown)) {
        ++res;
    }
    //right down
    if( ((color == RED && rightDown.first <= 9) || (color == BLACK && rightDown.first <= 4))
            && rightDown.second <= 8 && isEmptyOrEnemy(board, color, rightDown)) {
        ++res;
    }

    return res;
}


int getHorseMoveMethodsCnt(const pair<int,int> &oldP, PIECE_COLOR color, Board *board){
    int res = 0;
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
        ++res;

    //left2_top1
    if(isOnBoard(left2_top1) && isEmptyOrEnemy(board, color, left2_top1) &&
            board->getPieceType(oldP.first, oldP.second - 1) == NO_PIECE)
        ++res;

    //right1_top2
    if(isOnBoard(right1_top2) && isEmptyOrEnemy(board, color, right1_top2) &&
            board->getPieceType(oldP.first + 1, oldP.second) == NO_PIECE)
        ++res;

    //right2_top1
    if(isOnBoard(right2_top1) && isEmptyOrEnemy(board, color, right2_top1) &&
            board->getPieceType(oldP.first, oldP.second + 1) == NO_PIECE)
        ++res;

    //left1_down2
    if(isOnBoard(left1_down2) && isEmptyOrEnemy(board, color, left1_down2) &&
            board->getPieceType(oldP.first + 1, oldP.second) == NO_PIECE)
        ++res;

    //left2_down1
    if(isOnBoard(left2_down1) && isEmptyOrEnemy(board, color, left2_down1) &&
            board->getPieceType(oldP.first, oldP.second - 1) == NO_PIECE)
        ++res;

    //right1_down2
    if(isOnBoard(right1_down2) && isEmptyOrEnemy(board, color, right1_down2) &&
            board->getPieceType(oldP.first + 1, oldP.second) == NO_PIECE)
        ++res;

    //right2_down1
    if(isOnBoard(right2_down1) && isEmptyOrEnemy(board, color, right2_down1) &&
            board->getPieceType(oldP.first, oldP.second + 1) == NO_PIECE)
        ++res;

    return res;
}


int getChariotMoveMethodsCnt(const pair<int,int> &oldP, PIECE_COLOR color, Board *board) {
    int res = 0;
    //top
    for(int r = oldP.first - 1; r >= 0; --r) {
        if(board->getPieceType(r, oldP.second) == NO_PIECE) {
            ++res;
        } else {
            if(board->getPieceColor(r, oldP.second) != color)
                ++res;
            break;
        }
    }

    //down
    for(int r = oldP.first + 1; r <= 9; ++r) {
        if(board->getPieceType(r, oldP.second) == NO_PIECE) {
            ++res;
        } else {
            if(board->getPieceColor(r, oldP.second) != color)
                ++res;
            break;
        }
    }

    //left
    for(int c = oldP.second - 1; c >= 0; --c) {
        if(board->getPieceType(oldP.first, c) == NO_PIECE) {
            ++res;
        } else {
            if(board->getPieceColor(oldP.first, c) != color)
                ++res;
            break;
        }
    }

    //right
    for(int c = oldP.second + 1; c <= 8; ++c) {
        if(board->getPieceType(oldP.first, c) == NO_PIECE) {
            ++res;
        } else {
            if(board->getPieceColor(oldP.first, c) != color)
                ++res;
            break;
        }
    }

    return res;
}


int getCannoMoveMethodsCnt(const pair<int,int> &oldP, PIECE_COLOR color, Board *board){
    int res = 0;
    //top
    bool MidPiece = false;
    for(int r = oldP.first - 1; r >= 0; --r) {
        if(!MidPiece && board->getPieceType(r, oldP.second) == NO_PIECE) {
            ++res;
        } else {
            if(!MidPiece) {
                MidPiece = true;
            } else if(board->getPieceType(r, oldP.second) == NO_PIECE) {
                continue;
            } else if(board->getPieceColor(r, oldP.second) != color) {
                ++res;
                break;
            }
            else break;
        }
    }

    //down
    MidPiece = false;
    for(int r = oldP.first + 1; r <= 9; ++r) {
        if(!MidPiece && board->getPieceType(r, oldP.second) == NO_PIECE) {
            ++res;
        } else {
            if(!MidPiece) {
                MidPiece = true;
            } else if(board->getPieceType(r, oldP.second) == NO_PIECE) {
                continue;
            } else if(board->getPieceColor(r, oldP.second) != color) {
                ++res;
                break;
            }
            else break;
        }
    }

    //left
    MidPiece = false;
    for(int c = oldP.second - 1; c >= 0; --c) {
        if(!MidPiece && board->getPieceType(oldP.first, c) == NO_PIECE) {
            ++res;
        } else {
            if(!MidPiece) {
                MidPiece = true;
            } else if(board->getPieceType(oldP.first, c) == NO_PIECE) {
                continue;
            } else if(board->getPieceColor(oldP.first, c) != color) {
                ++res;
                break;
            }
            else break;
        }
    }

    //right
    MidPiece = false;
    for(int c = oldP.second + 1; c <= 8; ++c) {
        if(!MidPiece && board->getPieceType(oldP.first, c) == NO_PIECE) {
            ++res;
        }
        else {
            if(!MidPiece) {
                MidPiece = true;
            } else if(board->getPieceType(oldP.first, c) == NO_PIECE) {
                continue;
            } else if(board->getPieceColor(oldP.first, c) != color) {
                ++res;
                break;
            }
            else break;
        }
    }
    return res;
}


int getSoldierMoveMethodsCnt(const pair<int,int> &oldP, PIECE_COLOR color, Board *board) {
    int res = 0;
    if ((color == BLACK && oldP.first > 4) || (color == RED && oldP.first < 5)) {
        //left
        auto left = pair<int, int>{oldP.first, oldP.second - 1};
        if(isEmptyOrEnemy(board, color, left))
            ++res;
        //right
        auto right = pair<int, int>{oldP.first, oldP.second + 1};
        if((isEmptyOrEnemy(board, color, right)))
            ++res;
    }

    if (color == BLACK) {
        auto down = pair<int, int>{oldP.first + 1, oldP.second};
        if(isEmptyOrEnemy(board, color, down)) 
            ++res;
        return res;
    }

    if (color == RED) {
        auto top = pair<int, int>{oldP.first - 1, oldP.second};
        if(isEmptyOrEnemy(board, color, top)) 
            ++res;
        return res;
    }

    return res;
}





/**
 * @brief is p on the Board?
 * 
 * @param p Position 
 * @return true 
 * @return false 
 */
bool isOnBoard(pair<int, int> &p) {
    return p.first < 0 || p.first > 9 || p.second < 0 || p.second > 8? false : true;
}

/**
 * @brief Determine whether position pos of the board has no pieces or is the opposing piece
 * 
 * @param board 
 * @param color 
 * @param pos 
 * @return true 
 * @return false 
 */
bool isEmptyOrEnemy(Board* board, PIECE_COLOR color, pair<int, int> pos) {
    return board->getPieceType(pos.first, pos.second) == NO_PIECE
            || board->getPieceColor(pos.first, pos.second) != color;
}




