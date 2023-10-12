#pragma once

namespace ModelStatic
{
    namespace Cube
    {
        constexpr array<float,24> VertexData =
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
        constexpr array<uint16_t,36> IndexData =
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
    namespace Bird
    {
        constexpr array<float,15> VertexData =
        {
             0.00f,  0.25f,  1.00f,
             0.00f, -0.50f,  0.00f,
             0.00f,  0.00f,  2.00f,
             2.00f,  0.00f, -2.00f,
            -2.00f,  0.00f, -2.00f,
        };
        constexpr array<uint16_t,18> IndexData =
        {
            0, 2, 3,
            0, 4, 2,
            2, 4, 1,
            2, 1, 3,
            0, 3, 1,
            0, 1, 4
        };
    }
    namespace OverlapingTrianlges
    {
        constexpr array<float,27> VertexData =
        {
             2, 3, 1,
             3, 1, 1,
            -3, 1, 0,
            -3, 1, 1,
            -2, 3, 1,
             1,-3, 0,
             1,-3, 1,
            -1,-3, 1,
             2, 3, 0
        };
        constexpr array<uint16_t,9> IndexData =
        {
            0, 1, 2,
            3, 4, 5,
            6, 7, 8
        };
    }
}
