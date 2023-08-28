#pragma once

struct AABB
{
    Vector3 p0, p1;
};
struct Sphere
{
    Vector3 position;
    float radius;
};
float AABBMinX(const AABB* aabb)
{
    return MathMin(aabb->p0.x,aabb->p1.x);
}
float AABBMinY(const AABB* aabb)
{
    return MathMin(aabb->p0.y,aabb->p1.y);
}
float AABBMinZ(const AABB* aabb)
{
    return MathMin(aabb->p0.z,aabb->p1.z);
}
float AABBMaxX(const AABB* aabb)
{
    return MathMax(aabb->p0.x,aabb->p1.x);
}
float AABBMaxY(const AABB* aabb)
{
    return MathMax(aabb->p0.y,aabb->p1.y);
}
float AABBMaxZ(const AABB* aabb)
{
    return MathMax(aabb->p0.z,aabb->p1.z);
}
Vector3 AABBSize(const AABB* aabb)
{
    Vector3 result = aabb->p0-aabb->p1;
    result.x = MathAbs(result.x);
    result.y = MathAbs(result.y);
    result.z = MathAbs(result.z);
    return result;
}
Vector3 AABBWrapAround(const AABB* aabb, Vector3 point)
{
    auto size = AABBSize(aabb);
    if      (point.x < AABBMinX(aabb)) point.x += size.x;
    else if (point.x > AABBMaxX(aabb)) point.x -= size.x;
    if      (point.y < AABBMinY(aabb)) point.y += size.y;
    else if (point.y > AABBMaxY(aabb)) point.y -= size.y;
    if      (point.z < AABBMinZ(aabb)) point.z += size.z;
    else if (point.z > AABBMaxZ(aabb)) point.z -= size.z;
    return point;
}
Vector3 AABBShortPathIn(const AABB* aabb, Vector3 point)
{
    auto result = Vector3Zero();
    if      (point.x < AABBMinX(aabb)) result.x = AABBMinX(aabb) - point.x;
    else if (point.x > AABBMaxX(aabb)) result.x = AABBMaxX(aabb) - point.x;
    if      (point.y < AABBMinY(aabb)) result.y = AABBMinY(aabb) - point.y;
    else if (point.y > AABBMaxY(aabb)) result.y = AABBMaxY(aabb) - point.y;
    if      (point.z < AABBMinZ(aabb)) result.z = AABBMinZ(aabb) - point.z;
    else if (point.z > AABBMaxZ(aabb)) result.z = AABBMaxZ(aabb) - point.z;
    return result;
}
bool InsideOrTouching(Vector3 point, Sphere sphere)
{
    return Vector3Length(point-sphere.position) <= sphere.radius;
}
Vector3 ClosesSurfacePoint(Vector3 point, Sphere sphere)
{
    auto diff = point-sphere.position;
    auto dir = Vector3Normalize(diff);
    auto dist = Vector3Length(diff);
    if (dist < sphere.radius)
        return dir* sphere.radius;
    return sphere.position+dir*dist;
}
bool Raycast(Vector3 from, Vector3 dir, Sphere sphere, float* outDistance, Vector3* outPoint, Vector3* outNormal)
{
    Vector3 diff = from - sphere.position;

    float a = Vector3LengthNoRoot(dir);
    float b = Vector3Dot(dir, diff) * 2.0f;
    float c = Vector3LengthNoRoot(diff) - (sphere.radius * sphere.radius);
    float delta = b * b - 4.0f * a * c;

    if (delta < 0.0f)
        return false;

    float dist = (-b - MathSqrt(delta)) / (2.0f * a);

    if (dist < 0.0f)
        return false;

    Vector3 point = from + dir * dist;
    Vector3 normal = point - sphere.position;

    *outDistance = dist;
    *outPoint = point;
    *outNormal = normal;

    return true;
}