#pragma once

#include "Boid.h"
#include "BoidWorld.h"

class World
{
public:
    Camera camera;
    BoidWorld boidWorld;
    World()
    {
        // camera.position += Vector3Up()*110;
        // camera.position += Vector3Right()*175;
        // camera.position += -Vector3Forward()*175;
        // camera.yaw = MathToRadians(-45);
        // camera.pitch = MathToRadians(15);

        // camera.position += Vector3Up()*110;
        // camera.position += Vector3Right()*175;
        // camera.position += -Vector3Forward()*50;
        // camera.yaw = MathToRadians(-45);
        // camera.pitch = MathToRadians(15);

        camera.position += Vector3Up()*50;
    }
    float time;
    void Update(float deltaTime,
        bool left, bool up, bool down, bool right,
        bool w, bool a, bool s, bool d, bool e, bool q)
    {
        // time += deltaTime;
        UpdateCameraPosition(&camera, deltaTime, w, a, s, d, e, q);
        UpdateCameraRotation(&camera, deltaTime, left, up, down, right);
        boidWorld.Update(deltaTime);
    }
};