#include "platform_display.h"
#include <raylib.h>

static uint8_t *fb;
static int w, h;
static Texture2D screenTex;

void start_display(uint8_t *rgbBuffer, int width, int height) {
    fb = rgbBuffer;
    w = width;
    h = height;

    Image img = {
        .data = fb,
        .width = w,
        .height = h,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8
    };

    screenTex = LoadTextureFromImage(img);
}

void request_redraw(void) {
    UpdateTexture(screenTex, fb);

    BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(
            screenTex,
            (Rectangle){0, 0, w, -h},   // flip y-axis
            (Rectangle){0, 0, w * 2, h * 2},
            (Vector2){0, 0},
            0,
            WHITE
        );
    EndDrawing();
}
