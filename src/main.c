#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <stdlib.h>
#include <time.h>

// systems
#include "systems/graphicssystem.h"
#include "systems/cardsystem.h"

// components
#include "entities/board.h"

bool isRunning = true;
// mtx_t lock;

int main(int argc, char const *argv[]) {
    // TODO: write a small OS abstraction layer for threading/mutex/sleep
    // thrd_t threads[1];
    // int thread_ids[1] = {1};

    // start graphics state
    init_graphics();
    // thrd_create(&threads[0], update, &isRunning);

    // init game state
    srand(time(NULL));
    init_board();
    init_decks();
    
    // main game loop
    while (isRunning) {
        // remove once threading is done
        update(&isRunning);

        // 1. handle events
        // 2. update gamestate
    }

    // free_discard_pile();

    return 0;
}