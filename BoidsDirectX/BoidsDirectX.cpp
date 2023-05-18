#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>

#include <d3d11_1.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <assert.h>
#include <stdint.h>
#include "src/Math.h"
#include "src/Math3D.h"

#include "src/SubgenSingleton.h"
#include "src/Window.h"

enum GameAction
{
    GameActionMoveCamFwd,
    GameActionMoveCamBack,
    GameActionMoveCamLeft,
    GameActionMoveCamRight,
    GameActionTurnCamLeft,
    GameActionTurnCamRight,
    GameActionLookUp,
    GameActionLookDown,
    GameActionRaiseCam,
    GameActionLowerCam,
    GameActionCount
};
struct Constants
{
    float4x4 modelViewProj;
};
struct Camera
{
    float3 cameraPos;
    float rot1;
    float rot2;
};

float4x4 modelMatrix = {};
float4x4 viewMatrix = {};
float4x4 projMatrix = {};
float4x4 modelViewProj = {};
int indexCount;
bool windowWasResized = true; // To force initial perspectiveMat calculation
Camera camera;
float currentTimeInSeconds = 0;
bool global_keyIsDown[GameActionCount] = {};

HWND hwnd;
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

// void GetCurentDirectoryPath(char* result)
// {
//     wchar_t buffer[MAX_PATH] = {};
//     GetCurrentDirectoryW(MAX_PATH, (LPWSTR)buffer);

//     int i = 0;
//     while (buffer[i*2] != '\0')
//     {
//         result[i] = buffer[i*2];
//         i++;
//     }
// }
// void GetExeFilePath(char* result)
// {
//     wchar_t buffer[MAX_PATH] = {};
//     GetModuleFileName(NULL, (LPWSTR)buffer, MAX_PATH);

//     int i = 0;
//     while (buffer[i*2] != '\0')
//     {
//         result[i] = buffer[i*2];
//         i++;
//     }
// }
bool FileExists(LPCWSTR file)
{
    return GetFileAttributes(file) != INVALID_FILE_ATTRIBUTES;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    LRESULT result = 0;
    switch(msg)
    {
        case WM_KEYDOWN:
        case WM_KEYUP:
        {
            bool isDown = (msg == WM_KEYDOWN);

            switch (wparam)
            {
                case VK_ESCAPE : { DestroyWindow(hwnd);                                break; }
                case 'W'       : { global_keyIsDown[GameActionMoveCamFwd]    = isDown; break; }
                case 'A'       : { global_keyIsDown[GameActionMoveCamLeft]   = isDown; break; }
                case 'S'       : { global_keyIsDown[GameActionMoveCamBack]   = isDown; break; }
                case 'D'       : { global_keyIsDown[GameActionMoveCamRight]  = isDown; break; }
                case 'E'       : { global_keyIsDown[GameActionRaiseCam]      = isDown; break; }
                case 'Q'       : { global_keyIsDown[GameActionLowerCam]      = isDown; break; }
                case VK_UP     : { global_keyIsDown[GameActionLookUp]        = isDown; break; }
                case VK_LEFT   : { global_keyIsDown[GameActionTurnCamLeft]   = isDown; break; }
                case VK_DOWN   : { global_keyIsDown[GameActionLookDown]      = isDown; break; }
                case VK_RIGHT  : { global_keyIsDown[GameActionTurnCamRight]  = isDown; break; }
                default        : {                                                     break; }
            }

            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
        case WM_SIZE:
        {
            windowWasResized = true;
            break;
        }
        default:
            result = DefWindowProcW(hwnd, msg, wparam, lparam);
    }
    return result;
}
void ShowMessageBox(_In_opt_ LPCSTR lpText)
{
    MessageBoxA(nullptr, lpText, nullptr, MB_OK);
}
int CreateWindow2(HINSTANCE hInstance, HWND* outHWND)
{
    WNDCLASSEXW winClass = {};
    winClass.cbSize = sizeof(WNDCLASSEXW);
    winClass.style = CS_HREDRAW | CS_VREDRAW;
    winClass.lpfnWndProc = &WndProc;
    winClass.hInstance = hInstance;
    winClass.hIcon = LoadIconW(0, IDI_APPLICATION);
    winClass.hCursor = LoadCursorW(0, IDC_ARROW);
    winClass.lpszClassName = L"MyWindowClass";
    winClass.hIconSm = LoadIconW(0, IDI_APPLICATION);

    if(!RegisterClassExW(&winClass))
    {
        ShowMessageBox("RegisterClassEx failed");
        return GetLastError();
    }

    RECT initialRect = { 0, 0, 1024, 768 };
    AdjustWindowRectEx(&initialRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);
    LONG initialWidth = initialRect.right - initialRect.left;
    LONG initialHeight = initialRect.bottom - initialRect.top;

    HWND hwnd = CreateWindowExW
    (
        WS_EX_OVERLAPPEDWINDOW,
        winClass.lpszClassName,
        L"BoidsDirectX",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        initialWidth,
        initialHeight,
        0, 0, hInstance, 0
    );

    if(!hwnd)
    {
        ShowMessageBox("CreateWindowEx failed");
        return GetLastError();
    }

    *outHWND = hwnd;

    return 0;
}
int CreateRenderTargets(ID3D11Device* d3d11Device, IDXGISwapChain1* swapChain, ID3D11RenderTargetView** d3d11FrameBufferView, ID3D11DepthStencilView** depthBufferView)
{
    ID3D11Texture2D* d3d11FrameBuffer;
    HRESULT hResult = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&d3d11FrameBuffer);
    assert(SUCCEEDED(hResult));

    hResult = d3d11Device->CreateRenderTargetView(d3d11FrameBuffer, 0, d3d11FrameBufferView);
    assert(SUCCEEDED(hResult));

    D3D11_TEXTURE2D_DESC depthBufferDesc;
    d3d11FrameBuffer->GetDesc(&depthBufferDesc);

    d3d11FrameBuffer->Release();

    depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    ID3D11Texture2D* depthBuffer = {};
    d3d11Device->CreateTexture2D(&depthBufferDesc, nullptr, &depthBuffer);

    if (depthBuffer == nullptr)
        return 1;

    d3d11Device->CreateDepthStencilView(depthBuffer, nullptr, depthBufferView);

    depthBuffer->Release();

    return 0;
}
int CreateDeviceAndContext(ID3D11Device** outDevice, ID3D11DeviceContext** outContext)
{
    D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

    #if defined(DEBUG_BUILD)
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
    #endif

    HRESULT hResult = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE,
                                        0, creationFlags,
                                        featureLevels, ARRAYSIZE(featureLevels),
                                        D3D11_SDK_VERSION, outDevice, 0, outContext);
    assert(SUCCEEDED(hResult));
    return GetLastError();
}
int CreateSwapChain(ID3D11Device* d3d11Device, HWND hwnd, IDXGISwapChain1** d3d11SwapChain)
{
    HRESULT hResult;
    IDXGIFactory2* dxgiFactory;
    IDXGIDevice1* dxgiDevice;

    hResult = d3d11Device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&dxgiDevice);
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

    hResult = dxgiFactory->CreateSwapChainForHwnd(d3d11Device, hwnd, &d3d11SwapChainDesc, 0, 0, d3d11SwapChain);
    assert(SUCCEEDED(hResult));

    dxgiFactory->Release();

    return 0;
}
void EnableDebug(ID3D11Device* device)
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
int CompileShadersAndInputs(ID3D11Device* d3d11Device, ID3D11VertexShader** vertexShader, ID3D11PixelShader** pixelShader, ID3D11InputLayout** inputLayout)
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

        hResult = d3d11Device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, vertexShader);
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

        hResult = d3d11Device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, pixelShader);
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

        HRESULT hResult = d3d11Device->CreateInputLayout(inputElementDescArray, ARRAYSIZE(inputElementDescArray), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), inputLayout);
        assert(SUCCEEDED(hResult));
    }

    vsBlob->Release();
    psBlob->Release();

    return 0;
}
int CreateVertexBuffer(ID3D11Device* d3d11Device, ID3D11Buffer** vertexBuffer)
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

    HRESULT hResult = d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, vertexBuffer);
    assert(SUCCEEDED(hResult));

    return 0;
}
int CreateIndexBuffer(ID3D11Device* d3d11Device, ID3D11Buffer** indexBuffer)
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

    HRESULT hResult = d3d11Device->CreateBuffer(&indexBufferDesc, &indexSubresourceData, indexBuffer);
    assert(SUCCEEDED(hResult));

    return 0;
}
int CreateConstantBuffer(ID3D11Device* d3d11Device, ID3D11Buffer** constantBuffer)
{
    D3D11_BUFFER_DESC constantBufferDesc = {};
    // ByteWidth must be a multiple of 16, per the docs
    constantBufferDesc.ByteWidth      = sizeof(Constants) + 0xf & 0xfffffff0;
    constantBufferDesc.Usage          = D3D11_USAGE_DYNAMIC;
    constantBufferDesc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
    constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    HRESULT hResult = d3d11Device->CreateBuffer(&constantBufferDesc, nullptr, constantBuffer);
    assert(SUCCEEDED(hResult));

    return 0;
}
int CreateRasterizerState(ID3D11Device* d3d11Device, ID3D11RasterizerState** rasterizerState)
{
    D3D11_RASTERIZER_DESC rasterizerDesc = {};
    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_BACK;
    rasterizerDesc.FrontCounterClockwise = TRUE;

    d3d11Device->CreateRasterizerState(&rasterizerDesc, rasterizerState);

    return 0;
}
int CreateDepthStencilState(ID3D11Device* d3d11Device, ID3D11DepthStencilState** depthStencilState)
{
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
    depthStencilDesc.DepthEnable    = TRUE;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc      = D3D11_COMPARISON_LESS;

    d3d11Device->CreateDepthStencilState(&depthStencilDesc, depthStencilState);

    return 0;
}
void InitCamera(Camera* outCamera)
{
    camera =
    {
        { 0, 0, 2 },
        0,
        0
    };
}
float4x4 ToViewMatrix(Camera* camera)
{
    return
        translationMat(-camera->cameraPos) *
        rotateYMat(camera->rot1) *
        rotateXMat(camera->rot2);
}
void UpdateCamera(float deltaTime, Camera* camera)
{
    float4x4 viewMatrix = ToViewMatrix(camera);
    float3 camFwdXZ = {-viewMatrix.m[2][0], -viewMatrix.m[2][1], -viewMatrix.m[2][2]};

    // float3 camFwdXZ = normalise({camera->cameraFwd.x, 0, camera->cameraFwd.z});
    float3 cameraRightXZ = cross(camFwdXZ, {0, 1, 0});

    const float CAM_MOVE_SPEED = 5.f; // in metres per second
    const float CAM_MOVE_AMOUNT = CAM_MOVE_SPEED * deltaTime;
    if(global_keyIsDown[GameActionMoveCamFwd])   camera->cameraPos += camFwdXZ * CAM_MOVE_AMOUNT;
    if(global_keyIsDown[GameActionMoveCamBack])  camera->cameraPos -= camFwdXZ * CAM_MOVE_AMOUNT;
    if(global_keyIsDown[GameActionMoveCamLeft])  camera->cameraPos -= cameraRightXZ * CAM_MOVE_AMOUNT;
    if(global_keyIsDown[GameActionMoveCamRight]) camera->cameraPos += cameraRightXZ * CAM_MOVE_AMOUNT;
    if(global_keyIsDown[GameActionRaiseCam])     camera->cameraPos.y += CAM_MOVE_AMOUNT;
    if(global_keyIsDown[GameActionLowerCam])     camera->cameraPos.y -= CAM_MOVE_AMOUNT;

    const float CAM_TURN_SPEED = (float)M_PI; // in radians per second
    const float CAM_TURN_AMOUNT = CAM_TURN_SPEED * deltaTime;
    if(global_keyIsDown[GameActionTurnCamLeft])   camera->rot1 -= CAM_TURN_AMOUNT;
    if(global_keyIsDown[GameActionTurnCamRight])  camera->rot1 += CAM_TURN_AMOUNT;
    if(global_keyIsDown[GameActionLookUp])        camera->rot2 -= CAM_TURN_AMOUNT;
    if(global_keyIsDown[GameActionLookDown])      camera->rot2 += CAM_TURN_AMOUNT;

    // Wrap yaw to avoid floating-point errors if we turn too far
    float M_PI2 = 2*(float)M_PI;
    while(camera->rot1 >=  M_PI2) camera->rot1 -= M_PI2;
    while(camera->rot1 <= -M_PI2) camera->rot1 += M_PI2;

    // Clamp pitch to stop camera flipping upside down
    float degree = degreesToRadians(85);
    if(camera->rot2 >  degree) camera->rot2 =  degree;
    if(camera->rot2 < -degree) camera->rot2 = -degree;
}
void UpdateConstantBuffer(ID3D11DeviceContext* d3d11DeviceContext, ID3D11Buffer* constantBuffer, float4x4 modelViewProj)
{
    D3D11_MAPPED_SUBRESOURCE mappedSubresource;
    d3d11DeviceContext->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
    Constants* constants = (Constants*)(mappedSubresource.pData);
    constants->modelViewProj = modelViewProj;
    d3d11DeviceContext->Unmap(constantBuffer, 0);
}
long GetTime()
{
    LARGE_INTEGER ticks;
    QueryPerformanceCounter(&ticks);
    return (long)ticks.QuadPart;
}
float GetDeltaTime(long oldTime, long newTime)
{
    LARGE_INTEGER perfFreq;
    QueryPerformanceFrequency(&perfFreq);
    LONGLONG perfCounterFrequency = perfFreq.QuadPart;

    double diff = (double)(newTime - oldTime);
    double ticksPerSecond = (double)perfCounterFrequency;

    return (float)(diff/ticksPerSecond);
}
void GetWindowInfo(HWND hwnd, int* outWindowWidth, int* outWindowHeight)
{
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    *outWindowWidth = clientRect.right - clientRect.left;
    *outWindowHeight = clientRect.bottom - clientRect.top;
}
void HandleWindowMessages(HWND hwnd, bool* outWindowWasClosed)
{
    MSG msg = {};
    *outWindowWasClosed = false;
    while(PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
    {
        if(msg.message == WM_QUIT)
        {
            *outWindowWasClosed = true;
        }
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}
void OnWindowResize(HWND hwnd, ID3D11DeviceContext* deviceContext, IDXGISwapChain1* swapChain, ID3D11RenderTargetView** renderTargetView, ID3D11DepthStencilView** depthStencilView)
{
    int windowWidth;
    int windowHeight;
    GetWindowInfo(hwnd,&windowWidth,&windowHeight);
    float windowWidthF = (float)windowWidth;
    float windowHeightF = (float)windowHeight;
    float windowAspectRatio = windowWidthF / windowHeightF;

    D3D11_VIEWPORT viewport = { 0.0f, 0.0f, windowWidthF, windowHeightF, 0.0f, 1.0f };
    deviceContext->RSSetViewports(1, &viewport);

    deviceContext->OMSetRenderTargets(0, 0, 0);

    (*renderTargetView)->Release();
    (*depthStencilView)->Release();

    HRESULT res = swapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
    assert(SUCCEEDED(res));

    CreateRenderTargets(device, swapChain, renderTargetView, depthStencilView);
    projMatrix = makePerspectiveMat(windowAspectRatio, degreesToRadians(84), 0.1f, 1000.f);
}
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    if(CreateWindow2(hInstance,&hwnd)) return 1;
    if(CreateDeviceAndContext(&device,&deviceContext)) return 1;

    #ifdef DEBUG_BUILD
    EnableDebug();
    #endif

    if(CreateSwapChain(device,hwnd,&swapChain)) return 1;
    if(CreateRenderTargets(device, swapChain, &renderTargetView, &depthStencilView)) return 1;
    if(CompileShadersAndInputs(device,&vertexShader,&pixelShader,&inputLayout)) return 1;
    if(CreateVertexBuffer(device,&vertexBuffer)) return 1;
    if(CreateIndexBuffer(device,&indexBuffer)) return 1;
    if(CreateConstantBuffer(device,&constantBuffer)) return 1;
    if(CreateRasterizerState(device,&rasterizerState)) return 1;
    if(CreateDepthStencilState(device,&depthStencilState)) return 1;

    deviceContext->RSSetState(rasterizerState);
    deviceContext->OMSetDepthStencilState(depthStencilState, 0);
    deviceContext->VSSetShader(vertexShader, nullptr, 0);
    deviceContext->PSSetShader(pixelShader, nullptr, 0);
    deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    deviceContext->IASetInputLayout(inputLayout);

    // InitCamera(&camera);
    // long oldTime = GetTime();

    // while(true)
    // {
    //     long newTime = GetTime();
    //     float deltaTime = GetDeltaTime(oldTime,newTime);
    //     oldTime = newTime;
    //     currentTimeInSeconds += deltaTime;

    //     bool mustExitLoop = false;
    //     HandleWindowMessages(hwnd,&mustExitLoop);
    //     if (mustExitLoop) break;

    //     if(windowWasResized)
    //     {
    //         OnWindowResize(hwnd,deviceContext,swapChain,&renderTargetView,&depthStencilView);
    //         windowWasResized = false;
    //     }

    //     UpdateCamera(deltaTime,&camera);

    //     // float duno = M_PI * currentTimeInSeconds;
    //     // modelMatrix = rotateXMat(-0.2f * duno) * rotateYMat(0.1f * duno) ;
    //     // modelMatrix =
    //     // {
    //     //     1,0,0,0,
    //     //     0,1,0,0,
    //     //     0,0,1,0,
    //     //     0,0,0,1
    //     // };
    //     viewMatrix = ToViewMatrix(&camera);
    //     FLOAT backgroundColor[4] = { 0.1f, 0.2f, 0.6f, 1.0f };
    //     deviceContext->ClearRenderTargetView(renderTargetView, backgroundColor);
    //     deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
    //     deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

    //     UINT stride = 3 * sizeof(float);
    //     UINT offset = 0;
    //     for (size_t i = 0; i < 3; i++)
    //     {
    //         float test1 = ((float)i)/3;
    //         modelMatrix =
    //         {
    //             1,0,0,0+test1,
    //             0,1,0,0+test1,
    //             0,0,1,0+test1,
    //             0,0,0,1
    //         };
    //         modelViewProj = modelMatrix * viewMatrix * projMatrix;
    //         deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    //         deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);
    //         UpdateConstantBuffer(deviceContext,constantBuffer,modelViewProj);
    //         deviceContext->DrawIndexed(indexCount, 0, 0);
    //     }

    //     swapChain->Present(1, 0);
    // }

    return 0;
}