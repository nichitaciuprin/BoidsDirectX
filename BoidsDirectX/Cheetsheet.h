#include <memory>
#include <vector>

struct Vector2
{
    float x, y;
};
struct Vector3
{
    float x, y, z;
};
struct Vector4
{
    float x, y, z, w;
};
struct Matrix
{
    float m[4][4];
};
struct AABB
{
    Vector3 p0, p1;
};
struct Camera
{
    Vector3 position;
    float rot1;
    float rot2;
};
struct Boid
{
    Vector3 position;
    Vector3 velocity;
};
struct BoidsWorld
{
    AABB bounds;
    std::vector<Boid> boids;
};
struct AppState
{
    Camera camera;
    BoidsWorld boidWorld;
};