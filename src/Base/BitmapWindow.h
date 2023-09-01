#pragma once

class BitmapWindow
{
public:
    static bool Exists()
    {
        return _hwnd != 0;
    }
    static void Create()
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

        int clientWidth = 40;
        int clientHeight = 400;
        RECT rect = { 0, 0, clientWidth, clientHeight };
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
        auto windowWidth = rect.right - rect.left;
        auto windowsHeight = rect.bottom - rect.top;

        _hwnd = CreateWindow(_windowClassName, _windowName,
                             WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                             500, 0, windowWidth, windowsHeight,
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
    static void GetBitmapInfo(uint32_t** outPixels, size_t* outWidth, size_t* outHeight)
    {
        *outPixels = _pixels;
        *outWidth = _width;
        *outHeight = _height;
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
    static int         _width;
    static int         _height;

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
int         BitmapWindow::_width = 0;
int         BitmapWindow::_height = 0;