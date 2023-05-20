#include "../Base/Base.h"
#include "../Boids/World.h"

void RenderBoids(const Camera* camera, int windowWidth, int windowHeight, const Vector3* positions, size_t count)
{
    float aspectRatio = (float)windowWidth/(float)windowHeight;
    Matrix viewMatrix = ToViewMatrix(camera);
    Matrix projMatrix = MakePerspectiveMat(aspectRatio, MathToRadians(84), 0.1f, 1000.f);
    // float duno = M_PI * currentTimeInSeconds;
    // modelMatrix = RotateXMatrix(-0.2f * duno) * RotateYMatrix(0.1f * duno) ;

    D3D::OnWindowResize(windowWidth,windowHeight);
    D3D::DrawBegin();

    for (size_t i = 0; i < count; i++)
    {
        Vector3 position = positions[i];
        Matrix modelMatrix =
        {
            1,0,0,position.x,
            0,1,0,position.y,
            0,0,1,position.z,
            0,0,0,1
        };
        Matrix modelViewProj = modelMatrix * viewMatrix * projMatrix;
        D3D::Draw(modelViewProj);
    }

    D3D::DrawEnd();
}



