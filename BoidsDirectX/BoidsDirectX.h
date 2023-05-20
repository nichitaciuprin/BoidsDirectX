#include "../Base/Base.h"

void RenderBoids(const Camera* camera, int windowWidth, int windowHeight, const float3* positions, size_t count)
{
    float aspectRatio = (float)windowWidth/(float)windowHeight;
    float4x4 viewMatrix = ToViewMatrix(camera);
    float4x4 projMatrix = makePerspectiveMat(aspectRatio, degreesToRadians(84), 0.1f, 1000.f);
    // float duno = M_PI * currentTimeInSeconds;
    // modelMatrix = rotateXMat(-0.2f * duno) * rotateYMat(0.1f * duno) ;

    D3D::OnWindowResize(windowWidth,windowHeight);
    D3D::DrawBegin();

    for (size_t i = 0; i < count; i++)
    {
        float3 position = positions[i];
        float4x4 modelMatrix =
        {
            1,0,0,position.x,
            0,1,0,position.y,
            0,0,1,position.z,
            0,0,0,1
        };
        float4x4 modelViewProj = modelMatrix * viewMatrix * projMatrix;
        D3D::Draw(modelViewProj);
    }

    D3D::DrawEnd();
}