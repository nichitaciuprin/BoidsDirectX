#include "BoidsDirectX.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    // auto world = make_unique<World>();
    // world->Render(hInstance);

    // while(true)
    // {
    //     world->Update(0.02f);
    //     world->Render(hInstance);
    // }

    auto d3d = D3D::GetInstance();
    auto window = make_unique<Window>(hInstance);
    auto cubeRecourse = make_unique<CubeRecourse>(d3d->GetDevice(),d3d->GetDeviceContext(),d3d->GetConstantBuffer());

    while(true)
    {
        // window->Clear();
        window->Update();
        auto proj = window->GetPerspective();
        // auto proj = Identity();
        auto view = Identity();
        auto model = TranslationMatrix({0,0,-10});
        auto result = model * view * proj;
        cubeRecourse->Draw(result);
        window->Present();

        Sleep(100);
    }

    return 0;
}