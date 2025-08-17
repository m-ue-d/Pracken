#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BITMAPFILEHEADER;

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
} BITMAPINFOHEADER;

#define BI_RGB 0
#define BI_RLE8 1
#define BI_RLE4 2
#define BI_BITFIELDS 3

#pragma pack(pop)

#define WIDTH 240
#define HEIGHT 240

uint8_t rgbBuffer[WIDTH * HEIGHT * 3];

uint8_t* load_bmp_rgb(const char* filename, int* outWidth, int* outHeight);

void fill_buffer(uint8_t r, uint8_t g, uint8_t b);

void fill_sprite(char* url, uint8_t x, uint8_t y);

#endif