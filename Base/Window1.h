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
    static void DrawBegin()
    {
        if (!inited) return;
        D3D::DrawBegin();
    }
    static void Draw(Vector3 position)
    {
        if (!inited) return;
        // D3D::Draw();
    }
    static void DrawEnd()
    {
        if (!inited) return;
        D3D::DrawEnd();
    }
private:
    static bool inited;
    static unique_ptr<Window> window;
};
bool Window1::inited = false;
unique_ptr<Window> Window1::window = nullptr;