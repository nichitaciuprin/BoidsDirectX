#include "BoidsDirectX.h"

void Render(Window* window, const Camera* camera, const vector<Boid> boids, const CubeRecourse* cube)
{
    window->Update();
    window->Clear();
    auto proj = window->GetPerspective();
    auto view = ToViewMatrix(camera);
    auto length = boids.size();
    for (size_t i = 0; i < length; i++)
    {
        auto boid = boids[i];
        auto model = TranslationMatrix(boid.pos);
        auto result = model * view * proj;
        cube->Draw(result);
    }
    window->Present();
}
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    // wchar_t buffer[MAX_PATH] = {};
    // GetModuleFileName(NULL, (LPWSTR)buffer, MAX_PATH);
    // auto result = wstring(buffer,sizeof(buffer));

    auto duno = GetExeFilePath();

    auto d3d = DeviceRecources::GetInstance();
    auto window = make_unique<Window>(hInstance);
    auto cubeRecourse = make_unique<CubeRecourse>(d3d->GetDevice(),d3d->GetDeviceContext(),d3d->GetConstantBuffer());

    auto world = make_unique<World>();
    Render(window.get(), &world->camera, world->boidWorld.boids, cubeRecourse.get());

    while(true)
    {
        world->Update(0.02f);
        Render(window.get(), &world->camera, world->boidWorld.boids, cubeRecourse.get());
    }

    return 0;
}