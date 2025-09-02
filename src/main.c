#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <stdlib.h>

//local libs
#include "tinycthread.h"

//systems
#include "systems/graphicssystem.h"
#include "systems/cardsystem.h"

bool isRunning = true;
mtx_t lock;

void p_sleep(int ms) {
    #ifdef _WIN32
        Sleep(ms);
    #else
        struct timespec ts = { ms / 1000, (ms % 1000) * 1000000 };
        nanosleep(&ts, NULL);
    #endif
}

int main(int argc, char const *argv[]) {
    thrd_t threads[1];
    int thread_ids[1] = {1};

    //start graphics state
    init_graphics();
    thrd_create(&threads[0], update, &isRunning);

    //init game state
    init_attack_deck();
    
    //main game loop
    while (isRunning) {
        // 1. handle events
        // 2. update gamestate
    }

    free_discard_pile();

    return 0;
}