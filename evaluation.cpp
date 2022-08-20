#include <board.h>


static const int pieceFightFactor = 1;
static const int piecePosFactor = 1;
static const int pieceFlexibilityFactor = 8;

int chariotPosValue[10][9] = {
    {206, 208, 207, 213, 214, 213, 207, 208, 206},
    {206, 212, 209, 216, 233, 216, 209, 212, 206},
    {206, 208, 207, 214, 216, 214, 207, 208, 206},
    {206, 213, 213, 216, 216, 216, 213, 213, 206},
    {208, 211, 211, 214, 215, 214, 211, 211, 208},
    {208, 212, 212, 214, 215, 214, 212, 212, 208},
    {204, 209, 204, 212, 214, 212, 204, 209, 204},
    {198, 208, 204, 212, 212, 212, 204, 208, 198},
    {200, 208, 206, 212, 200, 212, 206, 208, 200},
    {194, 206, 204, 212, 200, 212, 204, 206, 194},
};

int horsePosValue[10][9] = {
    {90, 90, 90, 96, 90, 96, 90, 90, 90},
    {90, 96, 103, 97, 94, 97, 103, 96, 90},
    {92, 98, 99, 103, 99, 103, 99, 98, 92},
    {93, 108, 100, 107, 100, 107, 100, 108, 93},
    {90, 100, 99, 103, 104, 103, 99, 100, 90},
    {90, 98, 101, 102, 103, 102, 101, 98, 90},
    {92, 94, 98, 95, 98, 95, 98, 94, 92},
    {93, 92, 94, 95, 92, 95, 94, 92, 93},
    {85, 90, 92, 93, 78, 93, 92, 90, 85},
    {88, 85, 90, 88, 90, 88, 90, 85, 88},
};

int cannoPosValue[10][9] = {
    {100, 100, 96, 91, 90, 91, 96, 100, 100},
    {98, 98, 96, 92, 89, 92, 96, 98, 98},
    {97, 97, 96, 91, 92, 91, 96, 97, 97},
    {96, 99, 99, 98, 100, 98, 99, 99, 96},
    {96, 96, 96, 96, 100, 96, 96, 96, 96},
    {95, 96, 99, 96, 100, 96, 99, 96, 95},
    {96, 96, 96, 96, 96, 96, 96, 96, 96},
    {97, 96, 100, 99, 101, 99, 100, 96, 97},
    {96, 97, 98, 98, 98, 98, 98, 97, 96},
    {96, 96, 97, 99, 99, 99, 97, 96, 96},
};

int soldierPosValue[10][9] = {
    {9, 9, 9, 11, 13, 11, 9, 9, 9},
    {19, 24, 32, 37, 37, 37, 32, 24, 19},
    {19, 23, 27, 29, 30, 29, 27, 23, 19},
    {14, 18, 20, 27, 29, 27, 20, 18, 14},
    {7, 0, 13, 0, 16, 0, 13, 0, 7},
    {7, 0, 7, 0, 15, 0, 7, 0, 7},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int generalPosValue[10][9] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 2, 2, 2, 0, 0, 0},
    {0, 0, 0, 11, 15, 11, 0, 0, 0},
};

int advisorPosValue[10][9] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 20, 0, 20, 0, 0, 0},
    {0, 0, 0, 0, 23, 0, 0, 0, 0},
    {0, 0, 0, 20, 0, 20, 0, 0, 0},
};

int elephantPosValue[10][9] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 20, 0, 0, 0, 20, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {18, 0, 0, 0, 23, 0, 0, 0, 18},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 20, 0, 0, 0, 20, 0, 0},
};

int getPiecePosValue(Piece &p) {
    int r= p.getPos().first;
    int c = p.getPos().second;
    PIECE_COLOR color = p.getColor();
    if (color == RED)
        return p.posEvalutaion[r][c];
    else
        return p.posEvalutaion[9 - r][c];
}

PIECE_COLOR evalutationFunction(Board *board) {
    int blackTotalValue = 0;
    int redTotalValue = 0;

    for (int i = 0; i < 32; ++i ){
       Piece p = board->getPiece(i);
       if (p.isExist()) {
           int pieceTotalValue = getPiecePosValue(p);
//           int piecePosValue = getPiecePosValue(p);
           //int pieceFightValue = p.getValue();
           //int pieceFlexibilityValue = p.getFlexibilityFactor() * p.getMoveMethodCnt(p.getPos(), p.getColor(), board)
            //            / p.getMaxMoveMethod();
           //int pieceTotalValue = pieceFightFactor * pieceFightValue + piecePosFactor * piecePosValue
                  //              +   pieceFlexibilityFactor * pieceFlexibilityValue;
           if (p.getColor() == RED)
               redTotalValue += pieceTotalValue;
           else blackTotalValue = pieceTotalValue;
       }
    }

    return blackTotalValue >= redTotalValue ? BLACK: RED;
}


