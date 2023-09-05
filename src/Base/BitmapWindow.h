#pragma once

class BitmapWindow
{
public:
    static bool Exists()
    {
        return _hwnd != 0;
    }
    static void Create(uint32_t x, uint32_t y, uint32_t clientWidth, uint32_t clientHeight)
    {
        if (Exists()) return;

        HINSTANCE hInstance = GetModuleHandle(NULL);

        if (!_windowClassRegistered)
        {
            _windowClassRegistered = true;
            WNDCLASS window_class = {};
            window_class.lpfnWndProc = _MessageHandler;
            window_class.hInstance = hInstance;
            window_class.lpszClassName = _windowClassName;
            RegisterClass(&window_class);
        }

        RECT rect = { 0, 0, (LONG)clientWidth, (LONG)clientHeight };
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
        auto windowWidth = rect.right - rect.left;
        auto windowHeight = rect.bottom - rect.top;

        _hwnd = CreateWindow(_windowClassName, _windowName,
                             WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                             (LONG)x, (LONG)y, windowWidth, windowHeight,
                             NULL, NULL, hInstance, NULL);

        // Removes window border
        LONG lStyle = GetWindowLong(_hwnd, GWL_STYLE);
        lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
        SetWindowLong(_hwnd, GWL_STYLE, lStyle);
        SetWindowPos(_hwnd, NULL, 0,0,0,0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);

        assert(_hwnd != NULL);
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
    static uint32_t GetPixel(uint32_t x, uint32_t y)
    {
        if (x > _width) return 0;
        if (y > _height) return 0;
        y = _height-1-y;
        return _pixels[x+y*_width];
    }
    static void SetPixel(uint32_t x, uint32_t y, uint32_t pixel)
    {
        if (x > _width) return;
        if (y > _height) return;
        y = _height-1-y;
        _pixels[x+y*_width] = pixel;
    }
    static void SetPixels(const unique_ptr<Bitmap>& bitmap)
    {
        if (!Exists()) return;
        for (uint32_t y = 0; y < _height; y++)
        for (uint32_t x = 0; x < _width; x++)
        {
            auto pixel = bitmap->GetPixel(x,y);
            SetPixel(x,y,pixel);
        }
    }
    static void SetPixels2(const unique_ptr<Bitmap>& bitmap)
    {
        if (!Exists()) return;

        auto width = bitmap->Width();
        auto height = bitmap->Height();

        if (width > _width)
            width = _width;

        if (height > _height)
            height = _height;

        // memcpy(bitmap->pixels.data(),_pixels,width*height);
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
    static BITMAPINFO  _bitmapinfo;
    static uint32_t*   _pixels;
    static uint32_t    _width;
    static uint32_t    _height;

    static void _InitBitmap()
    {
        _bitmapinfo.bmiHeader.biSize = sizeof(_bitmapinfo.bmiHeader);
        _bitmapinfo.bmiHeader.biPlanes = 1;
        _bitmapinfo.bmiHeader.biBitCount = 32;
        _bitmapinfo.bmiHeader.biCompression = BI_RGB;
        _hdc = CreateCompatibleDC(0);
    }
    static void _ResetBitmap(int clientWidth, int clientHeight)
    {
        _bitmapinfo.bmiHeader.biWidth  = clientWidth;
        _bitmapinfo.bmiHeader.biHeight = clientHeight;

        if (_hbitmap)
            DeleteObject(_hbitmap);

        _hbitmap = CreateDIBSection(NULL, &_bitmapinfo, DIB_RGB_COLORS, (void**)&_pixels, 0, 0);
        assert(_hbitmap != nullptr);
        SelectObject(_hdc, _hbitmap);

        _width  = clientWidth;
        _height = clientHeight;
    }
    static void _PaintBitmap()
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

    static LRESULT CALLBACK _MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        if (_hdc == 0)
            _InitBitmap();

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
                _PaintBitmap();
                break;
            }
            case WM_SIZE:
            {
                int clientWidth = LOWORD(lParam);
                int clientHeight = HIWORD(lParam);
                _ResetBitmap(clientWidth, clientHeight);
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
BITMAPINFO  BitmapWindow::_bitmapinfo = {};
uint32_t*   BitmapWindow::_pixels = 0;
uint32_t    BitmapWindow::_width = 0;
uint32_t    BitmapWindow::_height = 0;