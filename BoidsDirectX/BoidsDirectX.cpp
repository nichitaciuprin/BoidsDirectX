#include "BoidsDirectX.h"

void Main(HINSTANCE hInstance)
{
    float currentTimeInSeconds = 0;
    auto window = make_unique<Window>(hInstance);
    D3D::Init(window->GetHWND());
    Camera camera;
    camera.cameraPos = { 0, 0, 2 };
    camera.rot1 = 0;
    camera.rot2 = 0;

    while(true)
    {
        float deltaTime = GetDeltaTime2();
        currentTimeInSeconds += deltaTime;

        if (window->WindowShouldClose()) break;

        UpdateCameraRotation(&camera,deltaTime,window->keydown_VK_LEFT,window->keydown_VK_UP,window->keydown_VK_DOWN,window->keydown_VK_RIGHT);
        UpdateCameraPosition(&camera,deltaTime,window->keydown_W,window->keydown_A,window->keydown_S,window->keydown_D,window->keydown_E,window->keydown_Q);

        const size_t count = 3;
        float3 positions[count];
        for (size_t i = 0; i < count; i++)
        {
            float test1 = ((float)i)/count;
            positions[i] = { test1, test1, test1 };
        }
        RenderBoids(&camera,window->ClientWidth(),window->ClientHeight(),positions,count);
    }
}
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    Main(hInstance);

    return 0;
}