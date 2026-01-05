#include "platform_display.h"

// framebuffer pointer and dimensions
static uint8_t *fb;
static int w, h;

void start_display(uint8_t *rgbBuffer, int width, int height)
{
    fb = rgbBuffer;
    w = width;
    h = height;

    lcd_init(width, height);
}

void request_redraw(void)
{
    lcd_push_rgb(fb, w, h);
}
