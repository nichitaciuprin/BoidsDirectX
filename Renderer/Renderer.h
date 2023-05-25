#pragma once

#include <d3d11_1.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include "DeviceRecources.h"
#include "Window.h"
#include "CubeRecourse.h"

class Renderer
{
public:
    Renderer(HINSTANCE hInstance)
    {
        window = make_unique<Window>(hInstance);
        auto deviceRecources = DeviceRecources::GetInstance();
        auto device = deviceRecources->GetDevice();
        auto deviceContext = deviceRecources->GetDeviceContext();
        auto constantBuffer = deviceRecources->GetConstantBuffer();
        cubeModel = make_unique<CubeRecourse>(device,deviceContext,constantBuffer);
    }
    void Render(const Camera* camera, const vector<Boid> boids)
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
            cubeModel->Draw(result);
        }
        window->Present();
    }
private:
    unique_ptr<CubeRecourse> cubeModel;
    unique_ptr<Window> window;
};