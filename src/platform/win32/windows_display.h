#ifndef WIN32_DISPLAY_H
#define WIN32_DISPLAY_H

#include <stdint.h>

void start_display(uint8_t *rgbBuffer, int width, int height);
void request_redraw(void);

#endif