#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define UNICODE
#include <windows.h>
#include <d3d11_1.h>
#pragma comment(lib, "d3d11.lib")
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#include <assert.h>
#include <stdint.h>
#include "3DMaths.h"

bool global_windowDidResize = false;

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
    float3 cameraFwd;
    float cameraPitch;
    float cameraYaw;
};

bool global_keyIsDown[GameActionCount] = {};
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    LRESULT result = 0;
    switch(msg)
    {
        case WM_KEYDOWN:
        case WM_KEYUP:
        {
            bool isDown = (msg == WM_KEYDOWN);
            if(wparam == VK_ESCAPE)
                DestroyWindow(hwnd);
            else if(wparam == 'W')
                global_keyIsDown[GameActionMoveCamFwd] = isDown;
            else if(wparam == 'A')
                global_keyIsDown[GameActionMoveCamLeft] = isDown;
            else if(wparam == 'S')
                global_keyIsDown[GameActionMoveCamBack] = isDown;
            else if(wparam == 'D')
                global_keyIsDown[GameActionMoveCamRight] = isDown;
            else if(wparam == 'E')
                global_keyIsDown[GameActionRaiseCam] = isDown;
            else if(wparam == 'Q')
                global_keyIsDown[GameActionLowerCam] = isDown;
            else if(wparam == VK_UP)
                global_keyIsDown[GameActionLookUp] = isDown;
            else if(wparam == VK_LEFT)
                global_keyIsDown[GameActionTurnCamLeft] = isDown;
            else if(wparam == VK_DOWN)
                global_keyIsDown[GameActionLookDown] = isDown;
            else if(wparam == VK_RIGHT)
                global_keyIsDown[GameActionTurnCamRight] = isDown;
            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
        case WM_SIZE:
        {
            global_windowDidResize = true;
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
bool CreateRenderTargets(ID3D11Device* d3d11Device, IDXGISwapChain1* swapChain, ID3D11RenderTargetView** d3d11FrameBufferView, ID3D11DepthStencilView** depthBufferView)
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

    ID3D11Texture2D* depthBuffer;
    d3d11Device->CreateTexture2D(&depthBufferDesc, nullptr, &depthBuffer);

    d3d11Device->CreateDepthStencilView(depthBuffer, nullptr, depthBufferView);

    depthBuffer->Release();

    return true;
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
        L"08. Drawing a Cube",
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

    {
        HRESULT hResult = D3DCompileFromFile(L"shaders.hlsl", nullptr, nullptr, "vs_main", "vs_5_0", shaderCompileFlags, 0, &vsBlob, &shaderCompileErrorsBlob);
        if(FAILED(hResult))
        {
            const char* errorString = NULL;
            if(hResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
            {
                errorString = "Could not compile shader; file not found";
            }
            else if(shaderCompileErrorsBlob)
            {
                errorString = (const char*)shaderCompileErrorsBlob->GetBufferPointer();
                shaderCompileErrorsBlob->Release();
            }
            ShowMessageBox(errorString);
            return 1;
        }

        hResult = d3d11Device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, vertexShader);
        assert(SUCCEEDED(hResult));
    }

    {
        HRESULT hResult = D3DCompileFromFile(L"shaders.hlsl", nullptr, nullptr, "ps_main", "ps_5_0", shaderCompileFlags, 0, &psBlob, &shaderCompileErrorsBlob);
        if(FAILED(hResult))
        {
            const char* errorString = NULL;
            if(hResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
            {
                errorString = "Could not compile shader; file not found";
            }
            else if(shaderCompileErrorsBlob)
            {
                errorString = (const char*)shaderCompileErrorsBlob->GetBufferPointer();
                shaderCompileErrorsBlob->Release();
            }
            MessageBoxA(0, errorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
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
}
int indexCount;
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

    D3D11_SUBRESOURCE_DATA vertexSubresourceData = { vertexData };

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
void UpdateCamera(float deltaTime, Camera* camera)
{
    float3 camFwdXZ = normalise({camera->cameraFwd.x, 0, camera->cameraFwd.z});
    float3 cameraRightXZ = cross(camFwdXZ, {0, 1, 0});

    const float CAM_MOVE_SPEED = 5.f; // in metres per second
    const float CAM_MOVE_AMOUNT = CAM_MOVE_SPEED * deltaTime;
    if(global_keyIsDown[GameActionMoveCamFwd])   camera->cameraPos += camFwdXZ * CAM_MOVE_AMOUNT;
    if(global_keyIsDown[GameActionMoveCamBack])  camera->cameraPos -= camFwdXZ * CAM_MOVE_AMOUNT;
    if(global_keyIsDown[GameActionMoveCamLeft])  camera->cameraPos -= cameraRightXZ * CAM_MOVE_AMOUNT;
    if(global_keyIsDown[GameActionMoveCamRight]) camera->cameraPos += cameraRightXZ * CAM_MOVE_AMOUNT;
    if(global_keyIsDown[GameActionRaiseCam])     camera->cameraPos.y += CAM_MOVE_AMOUNT;
    if(global_keyIsDown[GameActionLowerCam])     camera->cameraPos.y -= CAM_MOVE_AMOUNT;

    const float CAM_TURN_SPEED = M_PI; // in radians per second
    const float CAM_TURN_AMOUNT = CAM_TURN_SPEED * deltaTime;
    if(global_keyIsDown[GameActionTurnCamLeft])   camera->cameraYaw += CAM_TURN_AMOUNT;
    if(global_keyIsDown[GameActionTurnCamRight])  camera->cameraYaw -= CAM_TURN_AMOUNT;
    if(global_keyIsDown[GameActionLookUp])        camera->cameraPitch += CAM_TURN_AMOUNT;
    if(global_keyIsDown[GameActionLookDown])      camera->cameraPitch -= CAM_TURN_AMOUNT;

    // Wrap yaw to avoid floating-point errors if we turn too far
    while(camera->cameraYaw >= 2*M_PI)
        camera->cameraYaw -= 2*M_PI;
    while(camera->cameraYaw <= -2*M_PI)
        camera->cameraYaw += 2*M_PI;

    // Clamp pitch to stop camera flipping upside down
    if(camera->cameraPitch > degreesToRadians(85))
        camera->cameraPitch = degreesToRadians(85);
    if(camera->cameraPitch < -degreesToRadians(85))
        camera->cameraPitch = -degreesToRadians(85);

    float4x4 viewMat = translationMat(-camera->cameraPos) * rotateYMat(-camera->cameraYaw) * rotateXMat(-camera->cameraPitch);
    camera->cameraFwd = {-viewMat.m[2][0], -viewMat.m[2][1], -viewMat.m[2][2]};
}
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    HWND hwnd;
    if(CreateWindow2(hInstance,&hwnd)) return 1;

    ID3D11Device* d3d11Device;
    ID3D11DeviceContext* d3d11DeviceContext;
    if(CreateDeviceAndContext(&d3d11Device,&d3d11DeviceContext)) return 1;

    #ifdef DEBUG_BUILD
    EnableDebug();
    #endif

    IDXGISwapChain1* d3d11SwapChain;
    if(CreateSwapChain(d3d11Device,hwnd,&d3d11SwapChain)) return 1;

    ID3D11RenderTargetView* d3d11FrameBufferView;
    ID3D11DepthStencilView* depthBufferView;
    CreateRenderTargets(d3d11Device, d3d11SwapChain, &d3d11FrameBufferView, &depthBufferView);

    ID3D11InputLayout* inputLayout;
    ID3D11VertexShader* vertexShader;
    ID3D11PixelShader* pixelShader;
    CompileShadersAndInputs(d3d11Device,&vertexShader,&pixelShader,&inputLayout);

    ID3D11Buffer* vertexBuffer;
    ID3D11Buffer* indexBuffer;
    ID3D11Buffer* constantBuffer;
    if(CreateVertexBuffer(d3d11Device,&vertexBuffer)) return 1;
    if(CreateIndexBuffer(d3d11Device,&indexBuffer)) return 1;
    if(CreateConstantBuffer(d3d11Device,&constantBuffer)) return 1;

    ID3D11RasterizerState* rasterizerState;
    if(CreateRasterizerState(d3d11Device,&rasterizerState)) return 1;

    ID3D11DepthStencilState* depthStencilState;
    if(CreateDepthStencilState(d3d11Device,&depthStencilState)) return 1;

    float4x4 perspectiveMat = {};
    global_windowDidResize = true; // To force initial perspectiveMat calculation

    // Timing
    LONGLONG startPerfCount = 0;
    LONGLONG perfCounterFrequency = 0;
    {
        LARGE_INTEGER perfCount;
        QueryPerformanceCounter(&perfCount);
        startPerfCount = perfCount.QuadPart;
        LARGE_INTEGER perfFreq;
        QueryPerformanceFrequency(&perfFreq);
        perfCounterFrequency = perfFreq.QuadPart;
    }
    double currentTimeInSeconds = 0.0;

    Camera camera =
    {
        { 0, 0, 2 },
        { 0, 0,-1 },
        0,
        0
    };

    // Main Loop
    bool isRunning = true;
    while(isRunning)
    {
        float deltaTime;
        {
            double previousTimeInSeconds = currentTimeInSeconds;
            LARGE_INTEGER perfCount;
            QueryPerformanceCounter(&perfCount);

            currentTimeInSeconds = (double)(perfCount.QuadPart - startPerfCount) / (double)perfCounterFrequency;
            deltaTime = (float)(currentTimeInSeconds - previousTimeInSeconds);
            if(deltaTime > (1.f / 60.f))
                deltaTime = (1.f / 60.f);
        }

        MSG msg = {};
        while(PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)
                isRunning = false;
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        // Get window dimensions
        int windowWidth, windowHeight;
        float windowAspectRatio;
        {
            RECT clientRect;
            GetClientRect(hwnd, &clientRect);
            windowWidth = clientRect.right - clientRect.left;
            windowHeight = clientRect.bottom - clientRect.top;
            windowAspectRatio = (float)windowWidth / (float)windowHeight;
        }

        if(global_windowDidResize)
        {
            d3d11DeviceContext->OMSetRenderTargets(0, 0, 0);
            d3d11FrameBufferView->Release();
            depthBufferView->Release();

            HRESULT res = d3d11SwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
            assert(SUCCEEDED(res));

            CreateRenderTargets(d3d11Device, d3d11SwapChain, &d3d11FrameBufferView, &depthBufferView);
            perspectiveMat = makePerspectiveMat(windowAspectRatio, degreesToRadians(84), 0.1f, 1000.f);

            global_windowDidResize = false;
        }

        UpdateCamera(deltaTime,&camera);

        float4x4 viewMat = translationMat(-camera.cameraPos) * rotateYMat(-camera.cameraYaw) * rotateXMat(-camera.cameraPitch);

        // Spin the cube
        float4x4 modelMat = rotateXMat(-0.2f * (float)(M_PI * currentTimeInSeconds)) * rotateYMat(0.1f * (float)(M_PI * currentTimeInSeconds)) ;

        // Calculate model-view-projection matrix to send to shader
        float4x4 modelViewProj = modelMat * viewMat * perspectiveMat;

        // Update constant buffer
        D3D11_MAPPED_SUBRESOURCE mappedSubresource;
        d3d11DeviceContext->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
        Constants* constants = (Constants*)(mappedSubresource.pData);
        constants->modelViewProj = modelViewProj;
        d3d11DeviceContext->Unmap(constantBuffer, 0);

        FLOAT backgroundColor[4] = { 0.1f, 0.2f, 0.6f, 1.0f };
        d3d11DeviceContext->ClearRenderTargetView(d3d11FrameBufferView, backgroundColor);

        d3d11DeviceContext->ClearDepthStencilView(depthBufferView, D3D11_CLEAR_DEPTH, 1.0f, 0);

        D3D11_VIEWPORT viewport = { 0.0f, 0.0f, (FLOAT)windowWidth, (FLOAT)windowHeight, 0.0f, 1.0f };
        d3d11DeviceContext->RSSetViewports(1, &viewport);

        d3d11DeviceContext->RSSetState(rasterizerState);
        d3d11DeviceContext->OMSetDepthStencilState(depthStencilState, 0);

        d3d11DeviceContext->OMSetRenderTargets(1, &d3d11FrameBufferView, depthBufferView);

        d3d11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        d3d11DeviceContext->IASetInputLayout(inputLayout);

        d3d11DeviceContext->VSSetShader(vertexShader, nullptr, 0);
        d3d11DeviceContext->PSSetShader(pixelShader, nullptr, 0);

        d3d11DeviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);

        UINT stride = 3 * sizeof(float);
        UINT offset = 0;

        d3d11DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
        d3d11DeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);

        d3d11DeviceContext->DrawIndexed(indexCount, 0, 0);

        d3d11SwapChain->Present(1, 0);
    }

    return 0;
}