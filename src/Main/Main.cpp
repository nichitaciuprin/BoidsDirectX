#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <memory>
#include <vector>
using namespace std;

struct Frame
{
    int width;
    int height;
    uint32_t* pixels;
};

//====================
#if RAND_MAX == 32767
#define Rand32() ((rand() << 16) + (rand() << 1) + (rand() & 1))
#else
#define Rand32() rand()
#endif
int pixelIndex = 0;
void ChangePixelsRandomly(uint32_t* pixels, int width, int height)
{
    int i1 = pixelIndex;
    int i2 = Rand32();
    int pixelCount = width*height;
    i1 = i1 % pixelCount;
    i2 = i2 % pixelCount;
    pixels[i1] = Rand32();
    pixels[i2] = 0;
    pixelIndex++;
}
//====================


Frame frame = {};
bool quit = false;
BITMAPINFO frame_bitmap_info;
HBITMAP frame_bitmap = 0;
HDC frame_device_context = 0;

LRESULT CALLBACK WindowProcessMessage(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_QUIT:
        case WM_DESTROY:
        {
            quit = true;
            break;
        }
        case WM_PAINT:
        {
            PAINTSTRUCT paint;
            HDC device_context;

            device_context = BeginPaint(window_handle, &paint);

            BitBlt(device_context,
                   paint.rcPaint.left, paint.rcPaint.top,
                   paint.rcPaint.right - paint.rcPaint.left,
                   paint.rcPaint.bottom - paint.rcPaint.top,
                   frame_device_context,
                   paint.rcPaint.left, paint.rcPaint.top,
                   SRCCOPY);

            EndPaint(window_handle, &paint);

            break;
        }
        case WM_SIZE:
        {
            int windowWidth = LOWORD(lParam);
            int windowHeight = HIWORD(lParam);

            frame_bitmap_info.bmiHeader.biWidth  = windowWidth;
            frame_bitmap_info.bmiHeader.biHeight = windowHeight;

            if (frame_bitmap) DeleteObject(frame_bitmap);
            frame_bitmap = CreateDIBSection(NULL, &frame_bitmap_info, DIB_RGB_COLORS, (void**)&frame.pixels, 0, 0);
            assert(frame_bitmap != nullptr);
            SelectObject(frame_device_context, frame_bitmap);

            frame.width  = windowWidth;
            frame.height = windowHeight;

            break;
        }
        default:
            return DefWindowProc(window_handle, message, wParam, lParam);
    }
    return 0;
}

int main()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    const wchar_t window_class_name[] = L"WindowClass1";
    WNDCLASS window_class = {};
    window_class.lpfnWndProc = WindowProcessMessage;
    window_class.hInstance = hInstance;
    window_class.lpszClassName = (LPCSTR)window_class_name;
    RegisterClass(&window_class);

    frame_bitmap_info.bmiHeader.biSize = sizeof(frame_bitmap_info.bmiHeader);
    frame_bitmap_info.bmiHeader.biPlanes = 1;
    frame_bitmap_info.bmiHeader.biBitCount = 32;
    frame_bitmap_info.bmiHeader.biCompression = BI_RGB;
    frame_device_context = CreateCompatibleDC(0);

    HWND window_handle = CreateWindow((PCSTR)window_class_name, "Drawing Pixels",
                                 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                 640, 300, 640, 480,
                                 NULL, NULL, hInstance, NULL);

    assert(window_handle != NULL);

    MSG message = {};

    while (true)
    {
        if (quit) break;

        while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            DispatchMessage(&message);
        }

        ChangePixelsRandomly(frame.pixels, frame.width, frame.height);

        InvalidateRect(window_handle, NULL, FALSE);
        UpdateWindow(window_handle);
    }

    return 0;
}
