#pragma once

#include "Boid.h"
#include "../Base/Base.h"
#include "BoidWorld.h"

class World
{
public:
    Camera camera;
    BoidWorld boidWorld;
    World()
    {
        camera.position += Vector3Up()*110;
        camera.position += Vector3Right()*175;
        camera.position += -Vector3Forward()*175;
        camera.rot1 = MathToRadians(-45);
        camera.rot2 = MathToRadians(15);
    }
    void Update(float deltaTime)
    {
        boidWorld.Update(deltaTime);
    }
};