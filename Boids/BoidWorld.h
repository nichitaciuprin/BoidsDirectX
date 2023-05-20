#pragma once

#include "Boid.h"

using namespace std;

class BoidWorld
{
public:
    AABB aabb;
    vector<Boid> boids;
    BoidWorld()
    {
        aabb.p0 = Vector3Backward() + Vector3Left();
        aabb.p1 = Vector3Forward() + Vector3Right();
        auto size = 50.0f;
        aabb.p0 *= size;
        aabb.p1 *= size;
        aabb.p1 += Vector3Up()*size*2;
        for (int i = 0; i < boidCount; i++)
            boids.push_back(Boid(aabb));
    }
    void Update(float deltaTime)
    {
        Boid::Update(boids,aabb,deltaTime);
    }
private:
    int boidCount = 400;
};