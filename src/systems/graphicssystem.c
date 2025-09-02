#include "graphicssystem.h"

uint8_t* load_bmp_rgb(const char* filename, int* outWidth, int* outHeight) {
    FILE *img = fopen(filename, "rb");
    if (img == NULL) {
        printf("Not able to open the file.\n");
        return NULL;
    }

    BITMAPFILE_HEADER fileHeader;
    if (fread(&fileHeader, sizeof(fileHeader), 1, img) != 1) {
        printf("Failed to read BMP file header.\n");
        fclose(img);
        return NULL;
    }

    if (fileHeader.bfType != 0x4D42) {
        printf("Not a valid BMP file.\n");
        fclose(img);
        return NULL;
    }

    BITMAPINFO_HEADER infoHeader;
    if (fread(&infoHeader, sizeof(infoHeader), 1, img) != 1) {
        printf("Failed to read BMP info header.\n");
        fclose(img);
        return NULL;
    }

    if (infoHeader.biBitCount != 32 || (infoHeader.biCompression > BI_RGB  && infoHeader.biCompression < BI_BITFIELDS)) {
        printf("Only uncompressed 32-bit BMP files are supported.\n");
        fclose(img);
        return NULL;
    }

    int width = infoHeader.biWidth;
    int height = infoHeader.biHeight;
    *outWidth = width;
    *outHeight = height;

    size_t imageSize = width * height * 3;
    uint8_t* rgb_data = (uint8_t*)malloc(imageSize);
    if (!rgb_data) {
        printf("Memory allocation failed.\n");
        fclose(img);
        return NULL;
    }

    fseek(img, fileHeader.bfOffBits, SEEK_SET);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint8_t bgra[4];
            if (fread(bgra, 1, 4, img) != 4) {
                printf("Failed to read pixel at (%d,%d)\n", x, y);
                free(rgb_data);
                fclose(img);
                return NULL;
            }

            int index = ((height - 1 - y) * width + x) * 3;
            rgb_data[index + 0] = bgra[2];  //r
            rgb_data[index + 1] = bgra[1];  //g
            rgb_data[index + 2] = bgra[0];  //b
        }
    }

    fclose(img);
    return rgb_data;
}

void fill_buffer(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        rgbBuffer[i * 3 + 0] = r;
        rgbBuffer[i * 3 + 1] = g;
        rgbBuffer[i * 3 + 2] = b;
    }
}

void fill_sprite(char* url, uint32_t x, uint32_t y) {
    int outWidth = 0;
    int outHeight = 0;

    uint8_t* sprite = load_bmp_rgb(url, &outWidth, &outHeight);
    if (!sprite) return;

    for (int row = 0; row < outHeight; row++) {
        int screenY = y + row;
        if (screenY < 0 || screenY >= HEIGHT) continue;

        for (int col = 0; col < outWidth; col++) {
            int screenX = x + col;
            if (screenX < 0 || screenX >= WIDTH) continue;

            int spriteIdx = (row * outWidth + col) * 3;
            int bufferIdx = (screenY * WIDTH + screenX) * 3;

            rgbBuffer[bufferIdx + 0] = sprite[spriteIdx + 0];  //r
            rgbBuffer[bufferIdx + 1] = sprite[spriteIdx + 1];  //g
            rgbBuffer[bufferIdx + 2] = sprite[spriteIdx + 2];  //b
        }
    }

    free(sprite);
}

void init_graphics() {
    fill_buffer(255,243,237);

    start_display(&rgbBuffer, WIDTH, HEIGHT);    //non blocking & platform dependant
}

void sleep_ms(long milliseconds) {
    #ifdef _WIN32
        Sleep((DWORD)milliseconds);
    #else
        struct timespec ts;
        ts.tv_sec = milliseconds / 1000;
        ts.tv_nsec = (milliseconds % 1000) * 1000000;
        nanosleep(&ts, NULL);
    #endif
}

void update(void* arg) {
    int frame = 0;
    int frame_delay = 1000 / FPS;

    struct timespec frame_start, frame_end;
    long elapsed_ms;

    volatile bool* isRunning = (volatile bool*)arg;
    while(isRunning) {
        timespec_get(&frame_start, TIME_UTC);
        
        //---- drawing logic ----
        fill_buffer(255,243,237);
        fill_sprite("../assets/cards/2OfClubs.bmp", (frame*8 % (WIDTH+31)) - 31, 0);
        //----     end      ----

        request_redraw();   //platform dependant
        
        timespec_get(&frame_end, TIME_UTC);
        elapsed_ms = (long)(frame_end.tv_sec - frame_start.tv_sec) * 1000 +
                     (frame_end.tv_nsec - frame_start.tv_nsec) / 1000000;

        if (elapsed_ms < frame_delay) {
            sleep_ms(frame_delay - elapsed_ms);
        }


        frame++;
    }

}