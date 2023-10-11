#pragma once

class ModelCube2
{
public:
    void CreateVertexBuffer()
    {
        float vertexData[] =
        {
            -0.5f,-0.5f,-0.5f,
            -0.5f,-0.5f, 0.5f,
            -0.5f, 0.5f,-0.5f,
            -0.5f, 0.5f, 0.5f,
             0.5f,-0.5f,-0.5f,
             0.5f,-0.5f, 0.5f,
             0.5f, 0.5f,-0.5f,
             0.5f, 0.5f, 0.5f
        };
    }
    void CreateIndexBuffer()
    {
        int indices[] =
        {
            0, 6, 4,
            0, 2, 6,
            0, 3, 2,
            0, 1, 3,
            2, 7, 6,
            2, 3, 7,
            4, 6, 7,
            4, 7, 5,
            0, 4, 5,
            0, 5, 1,
            1, 5, 7,
            1, 7, 3
        };
    }
};