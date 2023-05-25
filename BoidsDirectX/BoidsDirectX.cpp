#include "../Base/Base.h"
#include "../Boids/World.h"
#include "../Renderer/Renderer.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    auto renderer = make_unique<Renderer>(hInstance);

    auto world = make_unique<World>();
    renderer->Render(&world->camera, world->boidWorld.boids);

    while(true)
    {
        world->Update(0.02f);
        renderer->Render(&world->camera, world->boidWorld.boids);
    }

    return 0;
}