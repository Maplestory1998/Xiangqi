#include "aithread.h"


void runAiThread(GameController &gameController, PIECE_COLOR color) {
    mtx.lock();
    gameController.runAi(color);
    mtx.unlock();
}
