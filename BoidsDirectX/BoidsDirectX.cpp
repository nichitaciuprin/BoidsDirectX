#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <memory>
#include <assert.h>
#include <stdint.h>

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

    long oldTime = GetTime();

    while(true)
    {
        long newTime = GetTime();
        float deltaTime = GetDeltaTime(oldTime,newTime);
        oldTime = newTime;
        currentTimeInSeconds += deltaTime;

        window->HandleWindowMessages();
        if (window->IsWindowClosed()) break;

        projMatrix = makePerspectiveMat(window->AspectRation(), degreesToRadians(84), 0.1f, 1000.f);

        if(windowWasResized)
        {
            D3D::OnWindowResize(window->ClientWidth(),window->ClientHeight());
            windowWasResized = false;
        }

        UpdateCamera(&camera,deltaTime,
                     window->keydown_VK_LEFT,window->keydown_VK_UP,window->keydown_VK_DOWN,window->keydown_VK_RIGHT,
                     window->keydown_W,window->keydown_A,window->keydown_S,window->keydown_D,window->keydown_E,window->keydown_Q);

        // float duno = M_PI * currentTimeInSeconds;
        // modelMatrix = rotateXMat(-0.2f * duno) * rotateYMat(0.1f * duno) ;

        viewMatrix = ToViewMatrix(&camera);
        D3D::DrawBegin();

        for (size_t i = 0; i < 3; i++)
        {
            float test1 = ((float)i)/3;
            modelMatrix =
            {
                1,0,0,0+test1,
                0,1,0,0+test1,
                0,0,1,0+test1,
                0,0,0,1
            };
            modelViewProj = modelMatrix * viewMatrix * projMatrix;

            D3D::Draw(modelViewProj);
        }

        D3D::DrawEnd();
    }

    return 0;
}