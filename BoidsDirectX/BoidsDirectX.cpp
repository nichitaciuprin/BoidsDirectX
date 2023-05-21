#include "BoidsDirectX.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    auto boidsWorld = make_unique<World>();

    while(true)
    {
        auto deltaTime = GetDeltaTime2();

        boidsWorld->Update(deltaTime);
        boidsWorld->Render(hInstance);
        if (Window1::Closed()) break;
    }

    return 0;
}