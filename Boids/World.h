#pragma once

#include "BoidWorld.h"

class World
{
public:
    Camera camera;
    BoidWorld boidWorld;

    World()
    {
        // camera.position = {0,10,10};
        // cameraUp = Vector3Up();
        camera.position += Vector3Up()*110;
        camera.position += Vector3Right()*175;
        camera.position += -Vector3Forward()*175;
        camera.rot1 = MathToRadians(-45);
        camera.rot2 = MathToRadians(15);
        // cameraTarget = Vector3Up()*50;
    }
    void Update(float deltaTime)
    {
        // auto rotation = Quaternion::CreateFromAxisAngle(Vector3::Up,deltaTime/2);
        // cameraPosition = Vector3::Transform(cameraPosition,rotation);
        boidWorld.Update(deltaTime);
    }
};