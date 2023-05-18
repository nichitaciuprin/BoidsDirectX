#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <memory>
#include <assert.h>
#include <stdint.h>

#include <d3d11_1.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "src/Time.h"
#include "src/Math.h"
#include "src/Math3D.h"
#include "src/SubgenSingleton.h"
#include "src/Window.h"
#include "src/D3D.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    auto window = std::make_unique<Window>(hInstance);

    D3D::Init(window->GetHWND());

    float4x4 modelMatrix = {};
    float4x4 viewMatrix = {};
    float4x4 projMatrix = {};
    float4x4 modelViewProj = {};

    bool windowWasResized = true; // To force initial perspectiveMat calculation

    Camera camera =
    {
        { 0, 0, 2 },
        0,
        0
    };

    float currentTimeInSeconds = 0;

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