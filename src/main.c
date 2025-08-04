#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include "platform/win32/windows_setup.h"
#endif

#define WIDTH 240
#define HEIGHT 240

int main(int argc, char const *argv[])
{
    uint8_t *rgbBuffer = malloc(WIDTH * HEIGHT * 3);
    if (!rgbBuffer) return 1;

    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        rgbBuffer[i * 3 + 0] = 255;
        rgbBuffer[i * 3 + 1] = 0;
        rgbBuffer[i * 3 + 2] = 0;
    }

#ifdef _WIN32
    run_window(rgbBuffer, WIDTH, HEIGHT);
#endif

    free(rgbBuffer);
    return 0;
}