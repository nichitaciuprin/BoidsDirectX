#pragma once

#include <algorithm>
#include "winuser.h"
// #include <string.h>
#include <stdlib.h>
#include <string>

#include <d3d11_1.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

// using namespace std;
// using namespace DX;
// using namespace DirectX;
// using namespace DirectX::SimpleMath;
// using Microsoft::WRL::ComPtr;

class Window
{
public:
    Window(HINSTANCE hInstance, const std::string name, int x, int y, int width, int height)
    {
        MaybeRegisterClass(hInstance);

        // RECT rc = { x, y, width, height };
        // AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

        // auto width2 = rc.right - rc.left;
        // auto height2 = rc.bottom - rc.top;

        // auto wstringTemp = wstring(name.begin(), name.end());
        // auto cstringTemp = wstringTemp.c_str();
        // auto windowNameTemp = LPCWSTR(cstringTemp);

        // m_hwnd = CreateWindowExW(0, className, windowNameTemp, WS_OVERLAPPEDWINDOW,
        //     x, y, width2, height2, nullptr, nullptr, hInstance, nullptr);
        // if (!m_hwnd) throw;
        // ShowWindow(m_hwnd, SW_SHOWNORMAL);
        // GetClientRect(m_hwnd, &rc);

        // SetInstance(m_hwnd,this);

        // m_deviceResources = make_unique<DeviceResources>();
        // m_deviceResources->SetWindow(m_hwnd, width2, height2);
        // m_deviceResources->CreateDeviceResources();
        // m_deviceResources->CreateWindowSizeDependentResources();
        // auto context = m_deviceResources->GetD3DDeviceContext();
        // m_shape = GeometricPrimitive::CreateSphere(context,1);
        // m_box = GeometricPrimitive::CreateBox(context,Vector3(1,1,1));
        // m_ground = GeometricPrimitive::CreateBox(context,Vector3(100,1,100));
    }
    // void Update()
    // {
    //     MSG msg = {};
    //     while (PeekMessage(&msg, m_hwnd, 0, 0, PM_REMOVE))
    //     {
    //         TranslateMessage(&msg);
    //         DispatchMessage(&msg);
    //     }
    // }
    // void Clear()
    // {
    //     m_deviceResources->PIXBeginEvent(L"Clear");
    //     auto context = m_deviceResources->GetD3DDeviceContext();
    //     auto renderTarget = m_deviceResources->GetRenderTargetView();
    //     auto depthStencil = m_deviceResources->GetDepthStencilView();
    //     context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    //     context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    //     context->OMSetRenderTargets(1, &renderTarget, depthStencil);
    //     auto const viewport = m_deviceResources->GetScreenViewport();
    //     context->RSSetViewports(1, &viewport);
    //     m_deviceResources->PIXEndEvent();
    // }
    // void ToFullscreen()
    // {
    //     SetWindowLongPtr(m_hwnd, GWL_STYLE, WS_POPUP);
    //     SetWindowLongPtr(m_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST);
    //     auto uFlags = SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED;
    //     SetWindowPos(m_hwnd, HWND_TOP, 0, 0, 0, 0, uFlags);
    //     ShowWindow(m_hwnd, SW_SHOWMAXIMIZED);
    //     fullscreen = true;
    // }
    // void ToDefaultSize()
    // {
    //     SetWindowLongPtr(m_hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
    //     SetWindowLongPtr(m_hwnd, GWL_EXSTYLE, 0);
    //     auto uFlags = SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED;
    //     SetWindowPos(m_hwnd, HWND_TOP, 0, 0, defaultWidth, defaultHeight, uFlags);
    //     ShowWindow(m_hwnd, SW_SHOWNORMAL);
    //     fullscreen = false;
    // }
    // void PaintStart()
    // {
    //     m_deviceResources->PIXBeginEvent(L"Render");
    // }
    // void PaintEnd()
    // {
    //     m_deviceResources->PIXEndEvent();
    //     m_deviceResources->Present();
    // }
    // void PaintSetCamera(Vector3 position, Vector3 target, Vector3 up)
    // {
    //     m_view = Matrix::CreateLookAt(position, target, up);
    // }
    // void PaintSetPerpective()
    // {
    //     auto size = m_deviceResources->GetOutputSize();
    //     m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f, float(size.right) / float(size.bottom), 0.1f, 1000.f);
    // }
    // void PaintGround()
    // {
    //     auto groundPosition = Matrix::CreateWorld(Vector3::Zero+Vector3::Down/2, Vector3::Forward, Vector3::Up);
    //     m_ground->Draw(groundPosition,m_view,m_proj,Colors::Black);
    // }
    // void PaintSphere(Vector3 position)
    // {
    //     auto m_world = Matrix::CreateWorld(position, Vector3::Forward, Vector3::Up);
    //     m_shape->Draw(m_world,m_view,m_proj);
    // }
    // Vector2 DirectionWASD()
    // {
    //     auto axisY = Window::key_w + Window::key_s;
    //     auto axisX = Window::key_a + Window::key_d;
    //     auto result = Vector2(axisX, axisY);
    //     result.Normalize();
    //     return result;
    // }
    // Vector2 MouseLook()
    // {
    //     // TODO
    //     return Vector2::Zero;
    // }

private:
    static bool classRegistered;
    static const LPCWSTR className;
    static const LPCWSTR iconName;
    const int defaultWidth = 800;
    const int defaultHeight = 600;
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
    HWND                      m_hwnd;
    ID3D11Device*             m_device;
    ID3D11DeviceContext*      m_deviceContext;
    IDXGISwapChain1*          m_swapChain;
    ID3D11RenderTargetView*   m_renderTargetView;
    ID3D11DepthStencilView*   m_depthStencilView;
    ID3D11InputLayout*        m_inputLayout;
    ID3D11VertexShader*       m_vertexShader;
    ID3D11PixelShader*        m_pixelShader;
    ID3D11Buffer*             m_vertexBuffer;
    ID3D11Buffer*             m_indexBuffer;
    ID3D11Buffer*             m_constantBuffer;
    ID3D11RasterizerState*    m_rasterizerState;
    ID3D11DepthStencilState*  m_depthStencilState;
    static void MaybeRegisterClass(HINSTANCE hInstance)
    {
        if (classRegistered) return;
        WNDCLASSEXW windowClass = {};
        windowClass.cbSize = sizeof(WNDCLASSEXW);
        windowClass.style = CS_HREDRAW | CS_VREDRAW;
        windowClass.lpfnWndProc = WndProc;
        windowClass.hInstance = hInstance;
        windowClass.hIcon = LoadIconW(hInstance, iconName);
        windowClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
        windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        windowClass.lpszClassName = className;
        windowClass.hIconSm = LoadIconW(windowClass.hInstance, iconName);
        if (!RegisterClassExW(&windowClass)) throw;
        classRegistered = true;
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

        // auto m_deviceResources = window->m_deviceResources.get();
        // if (m_deviceResources == NULL)
        //     return DefWindowProc(hwnd, message, wParam, lParam);

        switch (message)
        {
            case WM_DISPLAYCHANGE:
                // m_deviceResources->UpdateColorSpace();
                break;
            case WM_MOVE:
                // auto outputSize = m_deviceResources->GetOutputSize();
                // m_deviceResources->WindowSizeChanged(outputSize.right, outputSize.bottom);
                break;
            case WM_SIZE:
                // if (wParam == SIZE_MINIMIZED && !window->minimized)
                // {
                //     window->minimized = true;
                // }
                // else if (window->minimized)
                // {
                //     window->minimized = false;
                // }
                // else if (!window->sizemove)
                // {
                //     window->OnWindowSizeChanged(LOWORD(lParam), HIWORD(lParam));
                // }
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
    // void OnWindowSizeChanged(int width, int height)
    // {
    //     if (!m_deviceResources->WindowSizeChanged(width, height))
    //         return;
    // }
};
bool Window::classRegistered = false;
const LPCWSTR Window::className = L"MyWindow";
const LPCWSTR Window::iconName = L"IDI_ICON";