#pragma once

class Renderer
{
public:
    Renderer(HINSTANCE hInstance)
    {
        window = make_unique<Window>(hInstance);
    }
    bool WindowWasClosed()
    {
        return window->Closed();
    }
    void DrawBegin()
    {
        if (WindowWasClosed()) return;
        window->Update();
        // D3D::OnWindowResize(window->ClientWidth(),window->ClientHeight());
        // D3D::DrawBegin();
    }
    void SetCamera(const Camera* camera)
    {
        if (window->Closed()) return;
        auto aspectRatio = (float)window->ClientWidth()/(float)window->ClientHeight();
        viewMatrix = ToViewMatrix(camera);
        projMatrix = MakePerspectiveMat(aspectRatio, (float)(M_PI / 4.f), 0.1f, 1000.f);
        // projMatrix = MakePerspectiveMat(aspectRatio, MathToRadians(84), 0.1f, 1000.f);
    }
    void DrawCube(Vector3 position)
    {
        if (window->Closed()) return;
        auto modelMatrix = TranslationMatrix(position);
        auto modelViewProj = modelMatrix * viewMatrix * projMatrix;
        // D3D::Draw(modelViewProj);
    }
    void DrawEnd()
    {
        if (window->Closed()) return;
        // D3D::DrawEnd();
    }
private:
    D3D* d3d;
    unique_ptr<Window> window = nullptr;
    Camera camera = {};
    Matrix viewMatrix = Identity();
    Matrix projMatrix = Identity();
};