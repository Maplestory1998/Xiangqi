#ifndef EVALUATION_H
#define EVALUATION_H
#include "board.h"

/**
 * @brief Position evaluation value of various pieces
 */
extern int chariotPosValue[10][9];
extern int horsePosValue[10][9];
extern int cannoPosValue[10][9];
extern int soldierPosValue[10][9];
extern int generalPosValue[10][9];
extern int advisorPosValue[10][9];
extern int elephantPosValue[10][9];

/**
 * @brief evalute Piece's Posistion Importance(Value)
 * @param p
 * @return
 */
int evalutePiecePosValue(Piece &p);

/**
 * @brief evalutationFunction
 * @param board
 * @return The side who has higher evalutaion value
 */
PIECE_COLOR evalutationFunction(Board *board);

#endif
