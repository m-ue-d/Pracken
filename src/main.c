#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include "platform/platform_display.h"
#endif

#define WIDTH 740
#define HEIGHT 740

uint8_t rgbBuffer[WIDTH * HEIGHT * 3];

void fill_buffer(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        rgbBuffer[i * 3 + 0] = r;
        rgbBuffer[i * 3 + 1] = g;
        rgbBuffer[i * 3 + 2] = b;
    }
}

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

    int color_index = 0;
    const uint8_t colors[3][3] = {
        {255, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    while (1) {
        fill_buffer(colors[color_index][0],
                    colors[color_index][1],
                    colors[color_index][2]);

        request_redraw();
        p_sleep(500);

        color_index = (color_index + 1) % 3;
    }

    return 0;
}