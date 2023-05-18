#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <memory>

#include <stdlib.h>

#include <d3d11_1.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <assert.h>
#include <stdint.h>
#include "src/Math.h"
#include "src/Math3D.h"

#include "src/SubgenSingleton.h"
#include "src/Time.h"
#include "src/Window.h"
#include "src/D3D.h"

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
bool windowWasResized = true; // To force initial perspectiveMat calculation
Camera camera;
float currentTimeInSeconds = 0;

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
void UpdateCameraRotation(Camera* camera, float deltaTime, bool left, bool up, bool down, bool right)
{
    float speed = (float)M_PI; // in radians per second
    float result = speed * deltaTime;
    if(left)   camera->rot1 -= result;
    if(up)     camera->rot2 -= result;
    if(down)   camera->rot2 += result;
    if(right)  camera->rot1 += result;

    // Wrap yaw to avoid floating-point errors if we turn too far
    float M_PI2 = 2*(float)M_PI;
    while(camera->rot1 >=  M_PI2) camera->rot1 -= M_PI2;
    while(camera->rot1 <= -M_PI2) camera->rot1 += M_PI2;

    // Clamp pitch to stop camera flipping upside down
    float degree = degreesToRadians(85);
    if(camera->rot2 >  degree) camera->rot2 =  degree;
    if(camera->rot2 < -degree) camera->rot2 = -degree;
}
void UpdateCameraPosition(Camera* camera, float deltaTime, bool w, bool a, bool s, bool d, bool e, bool q)
{
    float4x4 viewMatrix = ToViewMatrix(camera);
    float3 camFwdXZ = {-viewMatrix.m[2][0], -viewMatrix.m[2][1], -viewMatrix.m[2][2]};

    // float3 camFwdXZ = normalise({camera->cameraFwd.x, 0, camera->cameraFwd.z});
    float3 cameraRightXZ = cross(camFwdXZ, {0, 1, 0});

    const float CAM_MOVE_SPEED = 5.f; // in metres per second
    const float CAM_MOVE_AMOUNT = CAM_MOVE_SPEED * deltaTime;
    if(w) camera->cameraPos   += camFwdXZ * CAM_MOVE_AMOUNT;
    if(a) camera->cameraPos   -= camFwdXZ * CAM_MOVE_AMOUNT;
    if(s) camera->cameraPos   -= cameraRightXZ * CAM_MOVE_AMOUNT;
    if(d) camera->cameraPos   += cameraRightXZ * CAM_MOVE_AMOUNT;
    if(e) camera->cameraPos.y += CAM_MOVE_AMOUNT;
    if(q) camera->cameraPos.y -= CAM_MOVE_AMOUNT;
}
void UpdateCamera(Camera* camera, float deltaTime,
bool left, bool up, bool down, bool right,
bool w, bool a, bool s, bool d, bool e, bool q)
{
    UpdateCameraRotation(camera,deltaTime,left,up,down,right);
    UpdateCameraPosition(camera,deltaTime,w,a,s,d,e,q);
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    auto window = std::make_unique<Window>(hInstance);

    D3D::Init(window->GetHWND());

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