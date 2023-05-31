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
        // UpdateCameraPosition(camera,window->keydown_)
        Matrix model;
        Matrix view;
        Matrix proj;
        proj = window->GetPerspective();
        // proj = MatrixIdentity();
        // float scale = 1.0f/10.0f;
        // proj =
        // {
        //     scale,0,0,0,
        //     0,scale,0,0,
        //     0,0,scale,0,
        //     0,0,0,1
        // };
        // proj =
        // {
        //     1,0,0,0,
        //     0,1,0,0,
        //     0,0,0,1,
        //     0,0,1,0
        // };
        // view =
        // {
        //     1,0,0,0,
        //     0,1,0,0,
        //     0,0,1,0,
        //     0,0,0,1
        // };
        // view = MatrixView(camera->position,{0,50,0},Vector3Up());
        // view = MatrixView({0,0,0},{0,0,1},Vector3Up());
        view = MatrixView(camera);
        // view = MatrixIdentity();

        auto length = boids.size();
        for (size_t i = 0; i < length; i++)
        {
            auto boid = boids[i];
            model = MatrixTranslate(boid.position);
            auto result = proj * view * model;
            cubeModel->Draw(result);
        }

        {model = MatrixTranslate({0,0,3});
        auto result = proj * view * model;
        cubeModel->Draw(result);}
        // {model = MatrixTranslate({1,0,3});
        // auto result = proj * view * model;
        // cubeModel->Draw(result);}
        // {model = MatrixTranslate({0,0,-10});
        // auto result = proj * view * model;
        // cubeModel->Draw(result);}
        // model = MatrixTranslate({0,0,10});
        // auto result = proj * view * model;
        // cubeModel->Draw(result);
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