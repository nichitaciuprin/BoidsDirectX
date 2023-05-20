#include "BoidsDirectX.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    auto window = make_unique<Window>(hInstance);

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

    while(true)
    {
        float deltaTime = GetDeltaTime2();
        currentTimeInSeconds += deltaTime;

        window->HandleWindowMessages();
        if (window->IsWindowClosed()) break;

        if(windowWasResized)
        {
            D3D::OnWindowResize(window->ClientWidth(),window->ClientHeight());
            windowWasResized = false;
        }

        UpdateCamera(&camera,deltaTime,
                     window->keydown_VK_LEFT,window->keydown_VK_UP,window->keydown_VK_DOWN,window->keydown_VK_RIGHT,
                     window->keydown_W,window->keydown_A,window->keydown_S,window->keydown_D,window->keydown_E,window->keydown_Q);

        const size_t count = 3;
        float3 positions[count];
        for (size_t i = 0; i < count; i++)
        {
            float test1 = ((float)i)/count;
            positions[i] = { test1, test1, test1 };
        }
        RenderBoids(&camera,window->ClientWidth(),window->ClientHeight(),positions,count);
    }

    return 0;
}