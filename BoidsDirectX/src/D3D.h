#pragma once

#include <algorithm>
#include "winuser.h"
#include <string.h>
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

class D3D
{
public:
    static int Init(HWND hwnd)
    {
        this.hwnd = hwnd;

        if(CreateDeviceAndDeviceContext()) return 1;

        #ifdef DEBUG_BUILD
        EnableDebug();
        #endif

        if(CreateSwapChain()) return 1;
    }

private:
    // const int defaultWidth = 800;
    // const int defaultHeight = 600;
    HWND                      hwnd;
    ID3D11Device*             device;
    ID3D11DeviceContext*      deviceContext;
    IDXGISwapChain1*          swapChain;
    ID3D11RenderTargetView*   renderTargetView;
    ID3D11DepthStencilView*   depthStencilView;
    ID3D11InputLayout*        inputLayout;
    ID3D11VertexShader*       vertexShader;
    ID3D11PixelShader*        pixelShader;
    ID3D11Buffer*             vertexBuffer;
    ID3D11Buffer*             indexBuffer;
    ID3D11Buffer*             constantBuffer;
    ID3D11RasterizerState*    rasterizerState;
    ID3D11DepthStencilState*  depthStencilState;

    int InitD3D()
    {
        if(CreateDeviceAndDeviceContext()) return 1;

        #ifdef DEBUG_BUILD
        EnableDebug();
        #endif

        if(CreateSwapChain()) return 1;
    }
    int CreateDeviceAndDeviceContext()
    {
        D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
        UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

        #if defined(DEBUG_BUILD)
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        #endif

        HRESULT hResult = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE,
                                            0, creationFlags,
                                            featureLevels, ARRAYSIZE(featureLevels),
                                            D3D11_SDK_VERSION, &device, 0, &deviceContext);
        assert(SUCCEEDED(hResult));
        return GetLastError();
    }
    int CreateSwapChain()
    {
        HRESULT hResult;
        IDXGIFactory2* dxgiFactory;
        IDXGIDevice1* dxgiDevice;

        hResult = device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&dxgiDevice);
        assert(SUCCEEDED(hResult));

        IDXGIAdapter* dxgiAdapter;
        hResult = dxgiDevice->GetAdapter(&dxgiAdapter);
        assert(SUCCEEDED(hResult));
        dxgiDevice->Release();

        DXGI_ADAPTER_DESC adapterDesc;
        dxgiAdapter->GetDesc(&adapterDesc);

        OutputDebugStringA("Graphics Device: ");
        OutputDebugStringW(adapterDesc.Description);

        hResult = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)&dxgiFactory);
        assert(SUCCEEDED(hResult));
        dxgiAdapter->Release();

        DXGI_SWAP_CHAIN_DESC1 d3d11SwapChainDesc = {};
        d3d11SwapChainDesc.Width = 0; // use window width
        d3d11SwapChainDesc.Height = 0; // use window height
        d3d11SwapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
        d3d11SwapChainDesc.SampleDesc.Count = 1;
        d3d11SwapChainDesc.SampleDesc.Quality = 0;
        d3d11SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        d3d11SwapChainDesc.BufferCount = 2;
        d3d11SwapChainDesc.Scaling = DXGI_SCALING_STRETCH;
        d3d11SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        d3d11SwapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
        d3d11SwapChainDesc.Flags = 0;

        hResult = dxgiFactory->CreateSwapChainForHwnd(device, m_hwnd, &d3d11SwapChainDesc, 0, 0, &swapChain);
        assert(SUCCEEDED(hResult));

        dxgiFactory->Release();

        return 0;
    }
};