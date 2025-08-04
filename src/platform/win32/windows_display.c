#include "../platform_display.h"
#include <windows.h>

static uint8_t *g_rgbBuffer = NULL;
static int g_width = 240;
static int g_height = 240;
static HWND g_hwnd = NULL;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            BITMAPINFO bmi = { 0 };
            bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi.bmiHeader.biWidth = g_width;
            bmi.bmiHeader.biHeight = -g_height;
            bmi.bmiHeader.biPlanes = 1;
            bmi.bmiHeader.biBitCount = 24;
            bmi.bmiHeader.biCompression = BI_RGB;

            StretchDIBits(
                hdc,
                0, 0, g_width, g_height,
                0, 0, g_width, g_height,
                g_rgbBuffer,
                &bmi,
                DIB_RGB_COLORS,
                SRCCOPY
            );

            EndPaint(hwnd, &ps);
        } return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

void request_redraw(void) {
    if (g_hwnd) {
        InvalidateRect(g_hwnd, NULL, TRUE);
        UpdateWindow(g_hwnd);
    }
}

DWORD WINAPI window_thread(LPVOID lpParam) {
    const wchar_t CLASS_NAME[] = L"TRTPTMWindowClass";

    WNDCLASSW wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClassW(&wc);

    g_hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"TRTPTM",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 
        g_width, g_height,
        NULL, NULL, GetModuleHandle(NULL), NULL
    );

    if (!g_hwnd) return 1;

    ShowWindow(g_hwnd, SW_SHOW);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

void start_display(uint8_t *rgbBuffer, int width, int height) {
    g_rgbBuffer = rgbBuffer;
    g_width = width;
    g_height = height;

    DWORD threadId;
    CreateThread(NULL, 0, window_thread, NULL, 0, &threadId);
}