#pragma once

class BitmapWindow
{
public:
    static bool Exists()
    {
        return _hwnd != 0;
    }
    static void Create(int x, int y, int clientWidth, int clientHeight)
    {
        if (Exists()) return;

        HINSTANCE hInstance = GetModuleHandle(NULL);

        if (!_windowClassRegistered)
        {
            _windowClassRegistered = true;
            WNDCLASS window_class = {};
            window_class.lpfnWndProc = MessageHandler;
            window_class.hInstance = hInstance;
            window_class.lpszClassName = _windowClassName;
            RegisterClass(&window_class);
        }

        LONG lStyle = WS_VISIBLE;

        // Makes default window
        // lStyle += WS_OVERLAPPEDWINDOW;

        RECT rect = { 0, 0, (LONG)clientWidth, (LONG)clientHeight };
        AdjustWindowRect(&rect, lStyle, FALSE);
        auto windowWidth = rect.right - rect.left;
        auto windowHeight = rect.bottom - rect.top;

        InitBitmap();

        _hwnd = CreateWindow(_windowClassName, _windowName, lStyle,
                             (LONG)x, (LONG)y, windowWidth, windowHeight,
                             NULL, NULL, hInstance, NULL);

        assert(_hwnd != NULL);

        // Forces window to update style
        // Setting lStyle before CreateWindow() wont work
        SetWindowLong(_hwnd, GWL_STYLE, lStyle);
        SetWindowPos(_hwnd, NULL, 0,0,0,0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    static void Update()
    {
        if (!Exists()) return;

        MSG message = {};
        while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
            DispatchMessage(&message);

        InvalidateRect(_hwnd, NULL, FALSE);
        UpdateWindow(_hwnd);
    }
    static void Delete()
    {
        if (!Exists()) return;
        DestroyWindow(_hwnd);
        _hwnd = 0;
    }
    static void SetPixels(const unique_ptr<Bitmap>& bitmap)
    {
        if (!Exists()) return;

        auto width = MathMin(bitmap->Width(),_width);
        auto height = MathMin(bitmap->Height(),_height);

        // copying from Top-Down bitmap to Bottom-Up bitmap
        for (uint32_t y = 0; y < height; y++)
        for (uint32_t x = 0; x < width; x++)
        {
            auto pixel = bitmap->pixels[x+y*width];
            auto y2 = _height-1-y;
            _pixels[x+y2*_width] = pixel;
        }
    }
    static uint32_t GetClientWidth()
    {
        return _width;
    }
    static uint32_t GetClientHeight()
    {
        return _height;
    }

private:
    static HWND           _hwnd;
    static bool           _windowClassRegistered;
    static const LPCWSTR  _windowClassName;
    static const LPCWSTR  _windowName;

    static HDC         _hdc;
    static HBITMAP     _hbitmap;
    static uint32_t*   _pixels;
    static uint32_t    _width;
    static uint32_t    _height;

    static void InitBitmap()
    {
        _hdc = CreateCompatibleDC(0);
    }
    static void ResetBitmap(int clientWidth, int clientHeight)
    {
        BITMAPINFO bitmapinfo = {};
        bitmapinfo.bmiHeader.biSize = sizeof(bitmapinfo.bmiHeader);
        bitmapinfo.bmiHeader.biPlanes = 1;
        bitmapinfo.bmiHeader.biBitCount = 32;
        bitmapinfo.bmiHeader.biCompression = BI_RGB;
        bitmapinfo.bmiHeader.biWidth  = clientWidth;
        bitmapinfo.bmiHeader.biHeight = clientHeight;

        if (_hbitmap)
            DeleteObject(_hbitmap);

        _hbitmap = CreateDIBSection(NULL, &bitmapinfo, DIB_RGB_COLORS, (void**)&_pixels, 0, 0);
        assert(_hbitmap != nullptr);
        SelectObject(_hdc, _hbitmap);

        _width  = clientWidth;
        _height = clientHeight;
    }
    static void PaintBitmap()
    {
        PAINTSTRUCT paint;

        HDC device_context = BeginPaint(_hwnd, &paint);

        BitBlt(device_context,
                paint.rcPaint.left, paint.rcPaint.top,
                paint.rcPaint.right - paint.rcPaint.left,
                paint.rcPaint.bottom - paint.rcPaint.top,
                _hdc,
                paint.rcPaint.left, paint.rcPaint.top,
                SRCCOPY);

        EndPaint(_hwnd, &paint);
    }

    static LRESULT CALLBACK MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch(message)
        {
            case WM_QUIT:
            case WM_DESTROY:
            {
                _hwnd = 0;
                break;
            }
            case WM_PAINT:
            {
                PaintBitmap();
                break;
            }
            case WM_SIZE:
            {
                uint32_t clientWidth = LOWORD(lParam);
                uint32_t clientHeight = HIWORD(lParam);

                auto sizeChanged =
                    _width != clientWidth ||
                    _height != clientHeight;

                if (sizeChanged)
                    ResetBitmap(clientWidth, clientHeight);

                break;
            }
            case WM_KEYDOWN:
            case WM_KEYUP:
            {
                switch (wParam)
                {
                    case VK_ESCAPE : { DestroyWindow(hwnd); break; }
                    default        : {                      break; }
                }
                break;
            }
            case WM_GETMINMAXINFO:
            {
                // Sets windows size defaults
                LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
                lpMMI->ptMinTrackSize.x = 10;
                lpMMI->ptMinTrackSize.y = 10;
                break;
            }
            default: return DefWindowProc(hwnd, message, wParam, lParam);
        }
        return 0;
    }
};

HWND           BitmapWindow::_hwnd = 0;
bool           BitmapWindow::_windowClassRegistered = false;
const LPCWSTR  BitmapWindow::_windowClassName = L"WindowClass1";
const LPCWSTR  BitmapWindow::_windowName = L"WindowName1";

HDC         BitmapWindow::_hdc = 0;
HBITMAP     BitmapWindow::_hbitmap = 0;
uint32_t*   BitmapWindow::_pixels = 0;
uint32_t    BitmapWindow::_width = 0;
uint32_t    BitmapWindow::_height = 0;