#include "graphicssystem.h"

#include <raylib.h>
#include <string.h>

uint8_t rgbBuffer[GFX_WIDTH * GFX_HEIGHT * GFX_BPP];

// raylib target
static RenderTexture2D target;
static Texture2D cardTex;
static bool initialized = false;

static void copy_to_rgbbuffer(void){
    Image img = LoadImageFromTexture(target.texture);
    uint8_t *src = (uint8_t *)img.data; // RGBA8888

    for (int i = 0; i < GFX_WIDTH * GFX_HEIGHT; i++) {
        rgbBuffer[i * 3 + 0] = src[i * 4 + 0];
        rgbBuffer[i * 3 + 1] = src[i * 4 + 1];
        rgbBuffer[i * 3 + 2] = src[i * 4 + 2];
    }

    UnloadImage(img);
}

void init_graphics(void) {
    if (initialized) return;

    InitWindow(GFX_WIDTH * 2, GFX_HEIGHT * 2, "Pracken");
    SetTargetFPS(GFX_FPS);

    target  = LoadRenderTexture(GFX_WIDTH, GFX_HEIGHT);
    cardTex = LoadTexture("assets/cards/2OfClubs.png");

    memset(rgbBuffer, 0, sizeof(rgbBuffer));

    // init platform display (PC window / embedded LCD)
    start_display(rgbBuffer, GFX_WIDTH, GFX_HEIGHT);

    initialized = true;
}

void update(void *arg) {
    volatile bool *isRunning = (volatile bool *)arg;
    int frame = 0;

    while (*isRunning && !WindowShouldClose()) {
        int x = (frame * 8 % (GFX_WIDTH + 31)) - 31;

        // offscreen rendering
        BeginTextureMode(target);
            ClearBackground((Color){255, 243, 237, 255});
            DrawTexture(cardTex, x, 20, WHITE);
        EndTextureMode();

        copy_to_rgbbuffer();

        request_redraw();

        frame++;
    }

    UnloadTexture(cardTex);
    UnloadRenderTexture(target);
    CloseWindow();
}