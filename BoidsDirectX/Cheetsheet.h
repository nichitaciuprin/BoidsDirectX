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
union Matrix
{
    float m[4][4];
    Vector4 cols[4];
};
struct AABB
{
    Vector3 p0, p1;
};
struct Camera
{
    Vector3 cameraPos;
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