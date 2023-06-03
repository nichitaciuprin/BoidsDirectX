#pragma once

#include <d3d11_1.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include "DeviceRecources.h"
#include "Window.h"
#include "ModelCube.h"
#include "ModelBird.h"

class Renderer
{
public:
    Renderer(HINSTANCE hInstance)
    {
        window = make_unique<Window>(hInstance);
        model = make_unique<ModelBird>();
    }
    void Render(const Camera* camera, const vector<Boid> boids)
    {
        window->Update();
        window->Clear();

        Matrix world;
        Matrix view;
        Matrix proj;

        proj = window->GetPerspective();
        view = MatrixView(camera);

        auto length = boids.size();
        for (size_t i = 0; i < length; i++)
        {
            auto boid = boids[i];

            world = MatrixWorld(boid.position,Vector3Normalize(boid.velocity));
            auto transformation = MatrixTransformaton(world,view,proj);
            model->Draw(transformation);
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
    unique_ptr<ModelBird> model;
    unique_ptr<Window> window;
};