#pragma once

#include <algorithm>
#include <winuser.h>
#include <string.h>
#include <stdlib.h>
#include <string>

// using namespace std;
// using namespace DX;
// using namespace DirectX;
// using namespace DirectX::SimpleMath;
// using Microsoft::WRL::ComPtr;

class Window
{
public:
    Window(HINSTANCE hInstance)
    {
        windowClosed = false;

        MaybeRegisterClass(hInstance);

        RECT rc = { 0, 0, defaultWidth, defaultHeight };
        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
        auto width2 = rc.right - rc.left;
        auto height2 = rc.bottom - rc.top;
        m_hwnd = CreateWindowExW(0, className, className, WS_OVERLAPPEDWINDOW,
                                 CW_USEDEFAULT, CW_USEDEFAULT, width2, height2,
                                 nullptr, nullptr, hInstance, nullptr);
        if (!m_hwnd) throw;

        ShowWindow(m_hwnd, SW_SHOWNORMAL);
        GetClientRect(m_hwnd, &rc);

        SetInstance(m_hwnd,this);

        InitD3D();
    }
    void GetWindowInfo(int* outWindowWidth, int* outWindowHeight)
    {
        RECT clientRect;
        GetClientRect(m_hwnd, &clientRect);
        *outWindowWidth = clientRect.right - clientRect.left;
        *outWindowHeight = clientRect.bottom - clientRect.top;
    }
    bool WindowShouldClose()
    {
        MSG msg = {};
        while(PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)
            {
                windowClosed = true;
            }
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
        return windowClosed;
    }
    float AspectRation()
    {
        return (float)defaultWidth / (float)defaultHeight;
    }
    int ClientWidth() { return defaultWidth; }
    int ClientHeight() { return defaultHeight; }
    HWND GetHWND() { return m_hwnd; }

    bool keydown_W = false;
    bool keydown_A = false;
    bool keydown_S = false;
    bool keydown_D = false;
    bool keydown_E = false;
    bool keydown_Q = false;
    bool keydown_VK_UP = false;
    bool keydown_VK_LEFT = false;
    bool keydown_VK_DOWN = false;
    bool keydown_VK_RIGHT = false;

private:
    static bool classRegistered;
    static const LPCWSTR className;
    static const LPCWSTR iconName;
    const int defaultWidth = 800;
    const int defaultHeight = 600;
    HWND m_hwnd;
    bool windowClosed;
    static void MaybeRegisterClass(HINSTANCE hInstance)
    {
        if (classRegistered) return;
        WNDCLASSEXW windowClass = {};
        windowClass.cbSize = sizeof(WNDCLASSEXW);
        windowClass.style = CS_HREDRAW | CS_VREDRAW;
        windowClass.lpfnWndProc = WndProc;
        windowClass.hInstance = hInstance;
        windowClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
        windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        windowClass.lpszClassName = className;
        windowClass.hIcon = LoadIconW(hInstance, iconName);
        windowClass.hIconSm = LoadIconW(hInstance, iconName);
        if (!RegisterClassExW(&windowClass)) throw;
        classRegistered = true;

        // WNDCLASSEXW winClass = {};
        // winClass.cbSize = sizeof(WNDCLASSEXW);
        // winClass.style = CS_HREDRAW | CS_VREDRAW;
        // winClass.lpfnWndProc = &WndProc;
        // winClass.hInstance = hInstance;
        // winClass.hIcon = LoadIconW(0, IDI_APPLICATION);
        // winClass.hCursor = LoadCursorW(0, IDC_ARROW);
        // winClass.lpszClassName = L"MyWindowClass";
        // winClass.hIconSm = LoadIconW(0, IDI_APPLICATION);
    }
    static void SetInstance(HWND hwnd, Window* window)
    {
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
    }
    static Window* GetInstance(HWND hwnd)
    {
        return reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        auto window = GetInstance(hwnd);

        if (window == NULL)
            return DefWindowProc(hwnd, message, wParam, lParam);

        switch (message)
        {
            case WM_DESTROY:
            {
                window->windowClosed = true;
                break;
            }
            case WM_SIZE: // Window size was changed
                break;
            case WM_KEYDOWN:
            case WM_KEYUP:
            {
                bool isDown = (message == WM_KEYDOWN);
                switch (wParam)
                {
                    case VK_ESCAPE : { DestroyWindow(hwnd);               break; }
                    case 'W'       : { window->keydown_W        = isDown; break; }
                    case 'A'       : { window->keydown_A        = isDown; break; }
                    case 'S'       : { window->keydown_S        = isDown; break; }
                    case 'D'       : { window->keydown_D        = isDown; break; }
                    case 'E'       : { window->keydown_E        = isDown; break; }
                    case 'Q'       : { window->keydown_Q        = isDown; break; }
                    case VK_UP     : { window->keydown_VK_UP    = isDown; break; }
                    case VK_LEFT   : { window->keydown_VK_LEFT  = isDown; break; }
                    case VK_DOWN   : { window->keydown_VK_DOWN  = isDown; break; }
                    case VK_RIGHT  : { window->keydown_VK_RIGHT = isDown; break; }
                    default        : {                                    break; }
                }
                break;
            }
        }

        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    int InitD3D()
    {
        // if(CreateDeviceAndDeviceContext()) return 1;

        // #ifdef DEBUG_BUILD
        // EnableDebug();
        // #endif

        // if(CreateSwapChain()) return 1;

        return 1;
    }
    // void OnWindowSizeChanged(int width, int height)
    // {
    //     if (!m_deviceResources->WindowSizeChanged(width, height))
    //         return;
    // }
};
bool Window::classRegistered = false;
const LPCWSTR Window::className = L"BoidsDirectX";
const LPCWSTR Window::iconName = L"IDI_ICON";