#pragma once

#include <d3d11_1.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include "DeviceRecources.h"
#include "Window.h"
#include "CubeModel.h"

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
        cubeModel = make_unique<CubeModel>(device,deviceContext,constantBuffer);
    }
    void Render(const Camera* camera, const vector<Boid> boids)
    {
        window->Update();
        window->Clear();
        auto proj = window->GetPerspective();
        // auto view = ToViewMatrix(camera);
        auto view = ToViewMatrix(camera->position,{0,50,0},Vector3Up());
        // auto view = Identity();
        auto length = boids.size();
        for (size_t i = 0; i < length; i++)
        {
            auto boid = boids[i];
            auto model = TranslationMatrix(boid.position);
            auto result = model * view * proj;
            cubeModel->Draw(result);
        }
        window->Present();
    }
    bool WindowIsClosed() const
    {
        return window->Closed();
    }
private:
    unique_ptr<CubeModel> cubeModel;
    unique_ptr<Window> window;
};