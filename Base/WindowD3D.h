#pragma once

#include <algorithm>
#include <winuser.h>
#include <string.h>
#include <stdlib.h>
#include <string>

#include <d3d11_1.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "FileHelper.h"
#include "Math.h"

struct Constants
{
    Matrix modelViewProj;
};

class D3D
{
public:
    static int Init(HWND inHwnd)
    {
        if(inited) return 0;

        hwnd = inHwnd;

        if(CreateDeviceAndDeviceContext()) return 1;
        #ifdef DEBUG_BUILD
        EnableDebug();
        #endif
        if(CreateSwapChain()) return 1;
        if(CreateRenderTargets()) return 1;
        if(CompileShadersAndInputs()) return 1;
        if(CreateVertexBuffer()) return 1;
        if(CreateIndexBuffer()) return 1;
        if(CreateConstantBuffer()) return 1;
        if(CreateRasterizerState()) return 1;
        if(CreateDepthStencilState()) return 1;

        deviceContext->RSSetState(rasterizerState);
        deviceContext->OMSetDepthStencilState(depthStencilState, 0);
        deviceContext->VSSetShader(vertexShader, nullptr, 0);
        deviceContext->PSSetShader(pixelShader, nullptr, 0);
        deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
        deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        deviceContext->IASetInputLayout(inputLayout);

        inited = true;

        return 0;
    }
    static void DrawBegin()
    {
        if(!inited) return;
        FLOAT backgroundColor[4] = { 0.1f, 0.2f, 0.6f, 1.0f };
        deviceContext->ClearRenderTargetView(renderTargetView, backgroundColor);
        deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
        deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
    }
    static void Draw(Matrix modelViewProj)
    {
        if(!inited) return;
        UINT stride = 3 * sizeof(float);
        UINT offset = 0;
        deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
        deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);
        UpdateConstantBuffer(modelViewProj);
        deviceContext->DrawIndexed(indexCount, 0, 0);
    }
    static void DrawEnd()
    {
        if(!inited) return;
        swapChain->Present(1, 0);
    }
    static void OnWindowResize(int windowWidth, int windowHeight)
    {
        if(!inited) return;

        float windowWidthF = (float)windowWidth;
        float windowHeightF = (float)windowHeight;
        float windowAspectRatio = windowWidthF / windowHeightF;

        D3D11_VIEWPORT viewport = { 0.0f, 0.0f, windowWidthF, windowHeightF, 0.0f, 1.0f };
        deviceContext->RSSetViewports(1, &viewport);

        deviceContext->OMSetRenderTargets(0, 0, 0);

        renderTargetView->Release();
        depthStencilView->Release();

        HRESULT res = swapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
        assert(SUCCEEDED(res));

        CreateRenderTargets();
        // projMatrix = MakePerspectiveMat(windowAspectRatio, MathToRadians(84), 0.1f, 1000.f);
    }
    static void UpdateConstantBuffer(Matrix modelViewProj)
    {
        if(!inited) return;
        D3D11_MAPPED_SUBRESOURCE mappedSubresource;
        deviceContext->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
        Constants* constants = (Constants*)(mappedSubresource.pData);
        constants->modelViewProj = modelViewProj;
        deviceContext->Unmap(constantBuffer, 0);
    }

private:
    static bool                      inited;
    static HWND                      hwnd;
    static ID3D11Device*             device;
    static ID3D11DeviceContext*      deviceContext;
    static IDXGISwapChain1*          swapChain;
    static ID3D11RenderTargetView*   renderTargetView;
    static ID3D11DepthStencilView*   depthStencilView;
    static ID3D11InputLayout*        inputLayout;
    static ID3D11VertexShader*       vertexShader;
    static ID3D11PixelShader*        pixelShader;
    static ID3D11Buffer*             vertexBuffer;
    static ID3D11Buffer*             indexBuffer;
    static ID3D11Buffer*             constantBuffer;
    static ID3D11RasterizerState*    rasterizerState;
    static ID3D11DepthStencilState*  depthStencilState;
    static int indexCount;

    static int CreateDeviceAndDeviceContext()
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
    static int CreateSwapChain()
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

        hResult = dxgiFactory->CreateSwapChainForHwnd(device, hwnd, &d3d11SwapChainDesc, 0, 0, &swapChain);
        assert(SUCCEEDED(hResult));

        dxgiFactory->Release();

        return 0;
    }
    static int CreateRenderTargets()
    {
        ID3D11Texture2D* d3d11FrameBuffer;
        HRESULT hResult = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&d3d11FrameBuffer);
        assert(SUCCEEDED(hResult));

        hResult = device->CreateRenderTargetView(d3d11FrameBuffer, 0, &renderTargetView);
        assert(SUCCEEDED(hResult));

        D3D11_TEXTURE2D_DESC depthBufferDesc;
        d3d11FrameBuffer->GetDesc(&depthBufferDesc);

        d3d11FrameBuffer->Release();

        depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

        ID3D11Texture2D* depthBuffer = {};
        device->CreateTexture2D(&depthBufferDesc, nullptr, &depthBuffer);

        if (depthBuffer == nullptr)
            return 1;

        device->CreateDepthStencilView(depthBuffer, nullptr, &depthStencilView);

        depthBuffer->Release();

        return 0;
    }
    static void EnableDebug()
    {
        ID3D11Debug *d3dDebug = nullptr;
        device->QueryInterface(__uuidof(ID3D11Debug), (void**)&d3dDebug);
        if (d3dDebug)
        {
            ID3D11InfoQueue *d3dInfoQueue = nullptr;
            if (SUCCEEDED(d3dDebug->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)&d3dInfoQueue)))
            {
                d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
                d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
                d3dInfoQueue->Release();
            }
            d3dDebug->Release();
        }
    }
    static int CompileShadersAndInputs()
    {
        UINT shaderCompileFlags = 0;
        // Compiling with this flag allows debugging shaders with Visual Studio
        #if defined(DEBUG_BUILD)
        shaderCompileFlags |= D3DCOMPILE_DEBUG;
        #endif

        ID3DBlob* vsBlob;
        ID3DBlob* psBlob;
        ID3DBlob* shaderCompileErrorsBlob;

        auto fileName = L"shaders.hlsl";

        assert(FileExists(fileName));

        {
            HRESULT hResult = D3DCompileFromFile(fileName, nullptr, nullptr, "vs_main", "vs_5_0", shaderCompileFlags, 0, &vsBlob, &shaderCompileErrorsBlob);
            if(FAILED(hResult))
            {
                const char* errorString = (const char*)shaderCompileErrorsBlob->GetBufferPointer();
                shaderCompileErrorsBlob->Release();
                ShowMessageBox(errorString);
                return 1;
            }

            hResult = device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &vertexShader);
            assert(SUCCEEDED(hResult));
        }

        {
            HRESULT hResult = D3DCompileFromFile(fileName, nullptr, nullptr, "ps_main", "ps_5_0", shaderCompileFlags, 0, &psBlob, &shaderCompileErrorsBlob);
            if(FAILED(hResult))
            {
                const char* errorString = (const char*)shaderCompileErrorsBlob->GetBufferPointer();
                shaderCompileErrorsBlob->Release();
                ShowMessageBox(errorString);
                return 1;
            }

            hResult = device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &pixelShader);
            assert(SUCCEEDED(hResult));
        }

        {
            D3D11_INPUT_ELEMENT_DESC inputElementDesc;
            inputElementDesc.SemanticName = "POS";
            inputElementDesc.SemanticIndex = 0;
            inputElementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
            inputElementDesc.InputSlot = 0;
            inputElementDesc.AlignedByteOffset = 0;
            inputElementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
            inputElementDesc.InstanceDataStepRate = 0;

            D3D11_INPUT_ELEMENT_DESC inputElementDescArray[] = { inputElementDesc };

            HRESULT hResult = device->CreateInputLayout(inputElementDescArray, ARRAYSIZE(inputElementDescArray), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &inputLayout);
            assert(SUCCEEDED(hResult));
        }

        vsBlob->Release();
        psBlob->Release();

        return 0;
    }
    static int CreateVertexBuffer()
    {
        float vertexData[] =
        {
            -0.5f,-0.5f,-0.5f,
            -0.5f,-0.5f, 0.5f,
            -0.5f, 0.5f,-0.5f,
            -0.5f, 0.5f, 0.5f,
            0.5f,-0.5f,-0.5f,
            0.5f,-0.5f, 0.5f,
            0.5f, 0.5f,-0.5f,
            0.5f, 0.5f, 0.5f
        };

        D3D11_BUFFER_DESC vertexBufferDesc = {};
        vertexBufferDesc.ByteWidth = sizeof(vertexData);
        vertexBufferDesc.Usage     = D3D11_USAGE_IMMUTABLE;
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA vertexSubresourceData = { };
        vertexSubresourceData.pSysMem = vertexData;

        HRESULT hResult = device->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &vertexBuffer);
        assert(SUCCEEDED(hResult));

        return 0;
    }
    static int CreateIndexBuffer()
    {
        uint16_t indices[] =
        {
            0, 6, 4,
            0, 2, 6,
            0, 3, 2,
            0, 1, 3,
            2, 7, 6,
            2, 3, 7,
            4, 6, 7,
            4, 7, 5,
            0, 4, 5,
            0, 5, 1,
            1, 5, 7,
            1, 7, 3
        };

        indexCount = sizeof(indices) / sizeof(indices[0]);

        D3D11_BUFFER_DESC indexBufferDesc = {};
        indexBufferDesc.ByteWidth = sizeof(indices);
        indexBufferDesc.Usage     = D3D11_USAGE_IMMUTABLE;
        indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA indexSubresourceData = { indices };

        HRESULT hResult = device->CreateBuffer(&indexBufferDesc, &indexSubresourceData, &indexBuffer);
        assert(SUCCEEDED(hResult));

        return 0;
    }
    static int CreateConstantBuffer()
    {
        D3D11_BUFFER_DESC constantBufferDesc = {};
        // ByteWidth must be a multiple of 16, per the docs
        constantBufferDesc.ByteWidth      = sizeof(Constants) + 0xf & 0xfffffff0;
        constantBufferDesc.Usage          = D3D11_USAGE_DYNAMIC;
        constantBufferDesc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
        constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        HRESULT hResult = device->CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer);
        assert(SUCCEEDED(hResult));

        return 0;
    }
    static int CreateRasterizerState()
    {
        D3D11_RASTERIZER_DESC rasterizerDesc = {};
        rasterizerDesc.FillMode = D3D11_FILL_SOLID;
        rasterizerDesc.CullMode = D3D11_CULL_BACK;
        rasterizerDesc.FrontCounterClockwise = TRUE;
        device->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
        return 0;
    }
    static int CreateDepthStencilState()
    {
        D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
        depthStencilDesc.DepthEnable    = TRUE;
        depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        depthStencilDesc.DepthFunc      = D3D11_COMPARISON_LESS;
        device->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
        return 0;
    }
};
bool                      D3D::inited = false;
HWND                      D3D::hwnd = nullptr;
ID3D11Device*             D3D::device = nullptr;
ID3D11DeviceContext*      D3D::deviceContext = nullptr;
IDXGISwapChain1*          D3D::swapChain = nullptr;
ID3D11RenderTargetView*   D3D::renderTargetView = nullptr;
ID3D11DepthStencilView*   D3D::depthStencilView = nullptr;
ID3D11InputLayout*        D3D::inputLayout = nullptr;
ID3D11VertexShader*       D3D::vertexShader = nullptr;
ID3D11PixelShader*        D3D::pixelShader = nullptr;
ID3D11Buffer*             D3D::vertexBuffer = nullptr;
ID3D11Buffer*             D3D::indexBuffer = nullptr;
ID3D11Buffer*             D3D::constantBuffer = nullptr;
ID3D11RasterizerState*    D3D::rasterizerState = nullptr;
ID3D11DepthStencilState*  D3D::depthStencilState = nullptr;
int D3D::indexCount = 0;