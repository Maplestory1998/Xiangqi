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
    {0, 0,  BLACK_CHARIOT,  canChariotMove},
    {0, 1,  BLACK_HORSE,    canHorseMove},
    {0, 2,  BLACK_ELEPHANT, canElephantMove},
    {0, 3,  BLACK_ADVISOR,  canAdvisorMove},
    {0, 4,  BLACK_GENERAL,  canGeneralMove},
    {0, 5,  BLACK_ADVISOR,  canAdvisorMove},
    {0, 6,  BLACK_ELEPHANT, canElephantMove},
    {0, 7,  BLACK_HORSE,    canHorseMove},
    {0, 8,  BLACK_CHARIOT,  canChariotMove},
    {2, 1,  BLACK_CANNON,   canCannoMove},
    {2, 7,  BLACK_CANNON,   canCannoMove},
    {3, 0,  BLACK_SOLDIER,  canSoldierMove},
    {3, 2,  BLACK_SOLDIER,  canSoldierMove},
    {3, 4,  BLACK_SOLDIER,  canSoldierMove},
    {3, 6,  BLACK_SOLDIER,  canSoldierMove},
    {3, 8,  BLACK_SOLDIER,  canSoldierMove},

    {9, 0,  RED_CHARIOT,    canChariotMove},
    {9, 1,  RED_HORSE,      canHorseMove},
    {9, 2,  RED_ELEPHANT,   canElephantMove},
    {9, 3,  RED_ADVISOR,    canAdvisorMove},
    {9, 4,  RED_GENERAL,    canGeneralMove},
    {9, 5,  RED_ADVISOR,    canAdvisorMove},
    {9, 6,  RED_ELEPHANT,   canElephantMove},
    {9, 7,  RED_HORSE,      canHorseMove},
    {9, 8,  RED_CHARIOT,    canChariotMove},
    {7, 1,  RED_CANNON,     canCannoMove},
    {7, 7,  RED_CANNON,     canCannoMove},
    {6, 0,  RED_SOLDIER,    canSoldierMove},
    {6, 2,  RED_SOLDIER,    canSoldierMove},
    {6, 4,  RED_SOLDIER,    canSoldierMove},
    {6, 6,  RED_SOLDIER,    canSoldierMove},
    {6, 8,  RED_SOLDIER,    canSoldierMove},
};

Piece::Piece() : canPieceMove(nullptr),  m_exist(true) , m_board(&g_board)
{

}

void Piece::Init(int id)
{
    //m_row = g_initialPos[id].row;
    //m_col = g_initialPos[id].col;
    m_type = g_initialPos[id].type;
    canPieceMove = g_initialPos[id].func;

    m_color = id <= 15? BLACK: RED;

}


bool canGeneralMove(QPair<int, int> oldP, QPair<int, int> newP, PIECE_COLOR color, Board *board)
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

bool canAdvisorMove(QPair<int, int> oldP, QPair<int, int> newP, PIECE_COLOR color, Board *board)
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

bool canElephantMove(QPair<int, int> oldP, QPair<int, int> newP, PIECE_COLOR color, Board *board)
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

bool canHorseMove(QPair<int, int> oldP, QPair<int, int> newP, PIECE_COLOR color, Board *board)
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

bool canChariotMove(QPair<int, int> oldP, QPair<int, int> newP, PIECE_COLOR color, Board *board)
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

bool canCannoMove(QPair<int, int> oldP, QPair<int, int> newP, PIECE_COLOR color, Board *board)
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


bool canSoldierMove(QPair<int, int> oldP, QPair<int, int> newP, PIECE_COLOR color, Board *board)
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














