#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <stdlib.h>

#include "platform/platform_display.h"

//systems
#include "systems/graphicssystem.h"


void p_sleep(int ms) {
    #ifdef _WIN32
        Sleep(ms);
    #else
        struct timespec ts = { ms / 1000, (ms % 1000) * 1000000 };
        nanosleep(&ts, NULL);
    #endif
}

int main(int argc, char const *argv[]) {
    start_display(rgbBuffer, WIDTH, HEIGHT);    //non blocking
    
    //white background
    fill_buffer(255,243,237);
    
    //main game loop
    while (1) {
        
        //draw joker card sprite
        fill_sprite("../assets/cards/2OfClubs.bmp", 0, 0);
    }

    return 0;
}