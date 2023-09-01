#pragma once

HWND           TestWindow_hwnd = 0;
bool           TestWindow_windowClassRegistered = false;
const LPCWSTR  TestWindow_windowClassName = L"WindowClass1";
const LPCWSTR  TestWindow_windowsName = L"WindowName1";

HDC         TestWindow_hdc = 0;
HBITMAP     TestWindow_hbitmap = 0;
BITMAPINFO  TestWindow_bitmapinfo = {};
uint32_t*   TestWindow_pixels = 0;
int         TestWindow_width = 0;
int         TestWindow_height = 0;

LRESULT CALLBACK TestWindow_MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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
            PAINTSTRUCT paint;

            HDC device_context = BeginPaint(hwnd, &paint);

            BitBlt(device_context,
                   paint.rcPaint.left, paint.rcPaint.top,
                   paint.rcPaint.right - paint.rcPaint.left,
                   paint.rcPaint.bottom - paint.rcPaint.top,
                   TestWindow_hdc,
                   paint.rcPaint.left, paint.rcPaint.top,
                   SRCCOPY);

            EndPaint(hwnd, &paint);

            break;
        }
        case WM_SIZE:
        {
            int windowWidth = LOWORD(lParam);
            int windowHeight = HIWORD(lParam);

            cout << windowWidth << endl;

            TestWindow_bitmapinfo.bmiHeader.biWidth  = windowWidth;
            TestWindow_bitmapinfo.bmiHeader.biHeight = windowHeight;

            if (TestWindow_hbitmap) DeleteObject(TestWindow_hbitmap);
            TestWindow_hbitmap = CreateDIBSection(NULL, &TestWindow_bitmapinfo, DIB_RGB_COLORS, (void**)&TestWindow_pixels, 0, 0);
            assert(TestWindow_hbitmap != nullptr);
            SelectObject(TestWindow_hdc, TestWindow_hbitmap);

            TestWindow_width  = windowWidth;
            TestWindow_height = windowHeight;

            break;
        }
        default: return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
void TestWindow_Create()
{
    if (TestWindow_hwnd != 0) return;

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

    TestWindow_bitmapinfo.bmiHeader.biSize = sizeof(TestWindow_bitmapinfo.bmiHeader);
    TestWindow_bitmapinfo.bmiHeader.biPlanes = 1;
    TestWindow_bitmapinfo.bmiHeader.biBitCount = 32;
    TestWindow_bitmapinfo.bmiHeader.biCompression = BI_RGB;
    TestWindow_hdc = CreateCompatibleDC(0);

    int clientWidth = 640;
    int clientHeight = 480;
    RECT rc = { 0, 0, clientWidth, clientHeight };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    auto windowWidth = rc.right - rc.left;
    auto windowsHeight = rc.bottom - rc.top;
    // m_hwnd = CreateWindowExW(0, className, className, WS_OVERLAPPEDWINDOW,
    //                             CW_USEDEFAULT, CW_USEDEFAULT, width2, height2,
    //                             nullptr, nullptr, hInstance, nullptr);

    TestWindow_hwnd = CreateWindow(TestWindow_windowClassName,
                                   TestWindow_windowsName,
                                   WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                   0, 0, windowWidth, windowsHeight,
                                   NULL, NULL, hInstance, NULL);

    assert(TestWindow_hwnd != NULL);
}
bool TestWindow_Exists()
{
    return TestWindow_hwnd != 0;
}
void TestWindow_Update()
{
    if (TestWindow_hwnd == 0) return;

    MSG message = {};

    while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
    {
        DispatchMessage(&message);
    }

    // ChangePixelsRandomly(frame.pixels, frame.width, frame.height);

    InvalidateRect(TestWindow_hwnd, NULL, FALSE);
    UpdateWindow(TestWindow_hwnd);
}
void TestWindow_Delete()
{
    if (TestWindow_hwnd == 0) return;
    DestroyWindow(TestWindow_hwnd);
    TestWindow_hwnd = 0;
}