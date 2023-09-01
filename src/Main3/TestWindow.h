#pragma once

HWND           TestWindow_hwnd = 0;
bool           TestWindow_windowClassRegistered = false;
const LPCWSTR  TestWindow_windowClassName = L"WindowClass1";
const LPCWSTR  TestWindow_windowName = L"WindowName1";

//==============BITMAP==============
HDC         TestWindow_hdc = 0;
HBITMAP     TestWindow_hbitmap = 0;
BITMAPINFO  TestWindow_bitmapinfo = {};
uint32_t*   TestWindow_pixels = 0;
int         TestWindow_width = 0;
int         TestWindow_height = 0;

void TestWindow_InitBitmap()
{
    TestWindow_bitmapinfo.bmiHeader.biSize = sizeof(TestWindow_bitmapinfo.bmiHeader);
    TestWindow_bitmapinfo.bmiHeader.biPlanes = 1;
    TestWindow_bitmapinfo.bmiHeader.biBitCount = 32;
    TestWindow_bitmapinfo.bmiHeader.biCompression = BI_RGB;
    TestWindow_hdc = CreateCompatibleDC(0);
}
void TestWindow_ResetBitmap(int clientWidth, int clientHeight)
{
    TestWindow_bitmapinfo.bmiHeader.biWidth  = clientWidth;
    TestWindow_bitmapinfo.bmiHeader.biHeight = clientHeight;

    if (TestWindow_hbitmap)
        DeleteObject(TestWindow_hbitmap);

    TestWindow_hbitmap = CreateDIBSection(NULL, &TestWindow_bitmapinfo, DIB_RGB_COLORS, (void**)&TestWindow_pixels, 0, 0);
    assert(TestWindow_hbitmap != nullptr);
    SelectObject(TestWindow_hdc, TestWindow_hbitmap);

    TestWindow_width  = clientWidth;
    TestWindow_height = clientHeight;
}
void TestWindow_PaintBitmap()
{
    PAINTSTRUCT paint;

    HDC device_context = BeginPaint(TestWindow_hwnd, &paint);

    BitBlt(device_context,
            paint.rcPaint.left, paint.rcPaint.top,
            paint.rcPaint.right - paint.rcPaint.left,
            paint.rcPaint.bottom - paint.rcPaint.top,
            TestWindow_hdc,
            paint.rcPaint.left, paint.rcPaint.top,
            SRCCOPY);

    EndPaint(TestWindow_hwnd, &paint);
}
//==================================

LRESULT CALLBACK TestWindow_MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (TestWindow_hdc == 0)
        TestWindow_InitBitmap();

    switch(message)
    {
        case WM_QUIT:
        case WM_DESTROY:
        {
            TestWindow_hwnd = 0;
            break;
        }
        case WM_PAINT:
        {
            TestWindow_PaintBitmap();
            break;
        }
        case WM_SIZE:
        {
            int clientWidth = LOWORD(lParam);
            int clientHeight = HIWORD(lParam);
            TestWindow_ResetBitmap(clientWidth, clientHeight);
            break;
        }
        default: return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
bool TestWindow_Exists()
{
    return TestWindow_hwnd != 0;
}
void TestWindow_Create()
{
    if (TestWindow_Exists()) return;

    HINSTANCE hInstance = GetModuleHandle(NULL);

    if (!TestWindow_windowClassRegistered)
    {
        TestWindow_windowClassRegistered = true;
        WNDCLASS window_class = {};
        window_class.lpfnWndProc = TestWindow_MessageHandler;
        window_class.hInstance = hInstance;
        window_class.lpszClassName = TestWindow_windowClassName;
        RegisterClass(&window_class);
    }

    int clientWidth = 640;
    int clientHeight = 480;
    RECT rc = { 0, 0, clientWidth, clientHeight };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    auto windowWidth = rc.right - rc.left;
    auto windowsHeight = rc.bottom - rc.top;

    TestWindow_hwnd = CreateWindow(TestWindow_windowClassName,
                                   TestWindow_windowName,
                                   WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                   0, 0, windowWidth, windowsHeight,
                                   NULL, NULL, hInstance, NULL);

    assert(TestWindow_hwnd != NULL);
}
void TestWindow_Update()
{
    if (!TestWindow_Exists()) return;

    MSG message = {};

    while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
    {
        DispatchMessage(&message);
    }

    InvalidateRect(TestWindow_hwnd, NULL, FALSE);
    UpdateWindow(TestWindow_hwnd);
}
void TestWindow_Delete()
{
    if (!TestWindow_Exists()) return;

    DestroyWindow(TestWindow_hwnd);

    TestWindow_hwnd = 0;
}