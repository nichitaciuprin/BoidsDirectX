#include "../Base/Base.h"
#include "../Boids/World.h"
#include "../Renderer/Renderer.h"

int main()
{
    auto duno = GetExeDirectory();
    duno += L"\\";
    duno += L"shaders.hlsl";
    wcout << duno << endl;
    return 0;
}