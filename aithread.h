#ifndef AITHREAD_H
#define AITHREAD_H
#include <mutex>
#include "gamecontroller.h"

extern std::mutex mtx;

/**
 * @brief Run ai in sub thread
 * 
 * @param gameController 
 * @param color 
 */
void runAiThread(GameController &gameController, PIECE_COLOR color);

#endif // AITHREAD_H
