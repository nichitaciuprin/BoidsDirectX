#pragma once

namespace Model
{
    namespace Cube
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
}

// class Model
// {
// public:
//     virtual const vector<float>& Verteses() = 0;
//     // virtual const vector<int>& Indeces() = 0;
// };


// class Model2 : public Model
// {
// public:
//     const vector<float>& Verteses()
//     {
//         float vertexData[] =
//         {
//             -0.5f,-0.5f,-0.5f,
//             -0.5f,-0.5f, 0.5f,
//             -0.5f, 0.5f,-0.5f,
//             -0.5f, 0.5f, 0.5f,
//              0.5f,-0.5f,-0.5f,
//              0.5f,-0.5f, 0.5f,
//              0.5f, 0.5f,-0.5f,
//              0.5f, 0.5f, 0.5f
//         };

//         auto duno = vector<float>()
//     }
//     // vector<int>& CreateIndexBuffer()
//     // {
//     //     int indices[] =
//     //     {
//     //         0, 6, 4,
//     //         0, 2, 6,
//     //         0, 3, 2,
//     //         0, 1, 3,
//     //         2, 7, 6,
//     //         2, 3, 7,
//     //         4, 6, 7,
//     //         4, 7, 5,
//     //         0, 4, 5,
//     //         0, 5, 1,
//     //         1, 5, 7,
//     //         1, 7, 3
//     //     };
//     // }
// };