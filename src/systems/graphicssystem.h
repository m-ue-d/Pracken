#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


//local libs
#include "tinycthread.h"

#include "../platform/platform_display.h"

#pragma pack(push, 1)
typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BITMAPFILE_HEADER;

typedef struct {
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BITMAPINFO_HEADER;

#pragma pack(pop)

#ifndef BI_RGB
    #define BI_RGB 0
#endif
#ifndef BI_RLE8
    #define BI_RLE8 1
#endif
#ifndef BI_RLE4
    #define BI_RLE4 2
#endif
#ifndef BI_BITFIELDS
    #define BI_BITFIELDS 3
#endif

#define WIDTH 240
#define HEIGHT 240
#define FPS 32

uint8_t rgbBuffer[WIDTH * HEIGHT * 3];

uint8_t* load_bmp_rgb(const char* filename, int* outWidth, int* outHeight);

void fill_buffer(uint8_t r, uint8_t g, uint8_t b);

void fill_sprite(char* url, uint8_t x, uint8_t y);

void update(void* id);

void init_graphics();

#endif