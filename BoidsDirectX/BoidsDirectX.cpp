#include "../Base/Base.h"
#include "../Boids/World.h"
#include "../Renderer/Renderer.h"

#include "Directxmath.h"

// XMMATRIX XM_CALLCONV XMMatrixTranslation(
//   [in] float OffsetX,
//   [in] float OffsetY,
//   [in] float OffsetZ
// ) noexcept;

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    // auto a = D3DXMatrixTranslation(0,0,10);

    auto renderer = make_unique<Renderer>(hInstance);

    auto world = make_unique<World>();
    renderer->Render(&world->camera, world->boidWorld.boids);

    while(true)
    {
        world->Update(0.02f);
        renderer->Render(&world->camera, world->boidWorld.boids);
        if (renderer->WindowIsClosed())
            break;
    }

    return 0;
}