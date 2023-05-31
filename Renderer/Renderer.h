#pragma once

#include <d3d11_1.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include "DeviceRecources.h"
#include "Window.h"
#include "CubeModel.h"
#include "BirdModel.h"

class Renderer
{
public:
    Renderer(HINSTANCE hInstance)
    {
        window = make_unique<Window>(hInstance);
        cubeModel = make_unique<BirdModel>();
    }
    void Render(const Camera* camera, const vector<Boid> boids)
    {
        window->Update();
        window->Clear();

        Matrix model;
        Matrix view;
        Matrix proj;

        proj = window->GetPerspective();
        view = MatrixView(camera);

        auto length = boids.size();
        for (size_t i = 0; i < length; i++)
        {
                auto boid = boids[i];

            model = MatrixWorld(boid.position,Vector3Normalize(boid.velocity));
            auto transformation = MatrixTransformaton(model,view,proj);
            cubeModel->Draw(transformation);
        }

        {
            model = MatrixTranslate({0,50,0});
            auto transformation = MatrixTransformaton(model,view,proj);
            cubeModel->Draw(transformation);
        }

        window->Present();
    }
    bool WindowIsClosed() const
    {
        return window->Closed();
    }
    bool Keydown_W()        { return window->keydown_W; }
    bool Keydown_A()        { return window->keydown_A; }
    bool Keydown_S()        { return window->keydown_S; }
    bool Keydown_D()        { return window->keydown_D; }
    bool Keydown_E()        { return window->keydown_E; }
    bool Keydown_Q()        { return window->keydown_Q; }
    bool Keydown_VK_UP()    { return window->keydown_VK_UP; }
    bool Keydown_VK_LEFT()  { return window->keydown_VK_LEFT; }
    bool Keydown_VK_DOWN()  { return window->keydown_VK_DOWN; }
    bool Keydown_VK_RIGHT() { return window->keydown_VK_RIGHT; }
private:
    unique_ptr<BirdModel> cubeModel;
    unique_ptr<Window> window;
};