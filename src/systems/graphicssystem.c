#include "./graphicssystem.h";



uint8_t* load_bmp_rgb(const char* filename, int* outWidth, int* outHeight) {
    FILE *img = fopen(filename, "rb");
    if (img == NULL) {
        printf("Not able to open the file.\n");
        return NULL;
    }

    BITMAPFILEHEADER fileHeader;
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

    BITMAPINFOHEADER infoHeader;
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

    size_t imageSize = width * height * 3; // RGB only (no alpha)
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
            rgb_data[index + 0] = bgra[2];  // R
            rgb_data[index + 1] = bgra[1];  // G
            rgb_data[index + 2] = bgra[0];  // B
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

void fill_sprite(char* url, uint8_t x, uint8_t y) {
    int outWidth = 0;
    int outHeight = 0;

    uint8_t* sprite = load_bmp_rgb(url, &outWidth, &outHeight);
    
    for (int row = 0; row < outHeight; row++) {
        for (int col = 0; col < outWidth; col++) {
            int spriteIdx = (row * outWidth + col) * 3;
            int bufferIdx = ((y + row) * WIDTH + (x + col)) * 3;
            rgbBuffer[bufferIdx + 0] = sprite[spriteIdx + 0];  // R
            rgbBuffer[bufferIdx + 1] = sprite[spriteIdx + 1];  // G
            rgbBuffer[bufferIdx + 2] = sprite[spriteIdx + 2];  // B
        }
    }
    
    free(sprite);
}