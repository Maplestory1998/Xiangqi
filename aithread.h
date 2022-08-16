#ifndef AITHREAD_H
#define AITHREAD_H
#include <mutex>
#include "gamecontroller.h"

extern std::mutex mtx;
void runAiThread(GameController &gameController, PIECE_COLOR color);

#endif // AITHREAD_H
