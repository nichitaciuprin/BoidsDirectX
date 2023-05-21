#pragma once

class Window1
{
public:
    static void Init(HINSTANCE hInstance)
    {
        if (inited) return;
        window = make_unique<Window>(hInstance);
        inited = true;
    }
    static bool Closed()
    {
        return window->Closed();
    }
    static void DrawBegin()
    {
        if (!inited) return;
        window->Update();
        if (window->Closed()) return;
        D3D::OnWindowResize(window->ClientWidth(),window->ClientHeight());
        D3D::DrawBegin();
    }
    static void SetCamera(const Camera* camera)
    {
        if (window->Closed()) return;
        auto aspectRatio = (float)window->ClientWidth()/(float)window->ClientHeight();
        viewMatrix = ToViewMatrix(camera);
        projMatrix = MakePerspectiveMat(aspectRatio, (float)(M_PI / 4.f), 0.1f, 1000.f);
        // projMatrix = MakePerspectiveMat(aspectRatio, MathToRadians(84), 0.1f, 1000.f);
    }
    static void DrawCube(Vector3 position)
    {
        if (!inited) return;
        if (window->Closed()) return;
        auto modelMatrix = TranslationMatrix(position);
        auto modelViewProj = modelMatrix * viewMatrix * projMatrix;
        D3D::Draw(modelViewProj);
    }
    static void DrawEnd()
    {
        if (!inited) return;
        if (window->Closed()) return;
        D3D::DrawEnd();
    }
private:
    static bool inited;
    static unique_ptr<Window> window;
    static Camera camera;
    static Matrix viewMatrix;
    static Matrix projMatrix;
};
bool Window1::inited = false;
unique_ptr<Window> Window1::window = nullptr;
Camera Window1::camera = {};
Matrix Window1::viewMatrix = Identity();
Matrix Window1::projMatrix = Identity();