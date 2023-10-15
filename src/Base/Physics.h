// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.html

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
bool InsideSphere(Vector3 point, Sphere sphere)
{
    auto diff = point - sphere.position;
    return Vector3LengthSquared(diff) <= sphere.radius * sphere.radius;
}
bool Raycast(Vector3 origin, Vector3 dirNorm, Sphere sphere, float* outDistance, Vector3* outPoint, Vector3* outNormal)
{
    Vector3 v1 = sphere.position - origin;

    float v2Length = Vector3Dot(dirNorm, v1);

    // if (v2Length < 0) return false; // sphere is behind

    Vector3 v2 = dirNorm * v2Length;
    Vector3 v3 = v2 - v1;

    float v3LengthSquared = Vector3LengthSquared(v3);
    float radiusSquared = sphere.radius * sphere.radius;

    if (v3LengthSquared > radiusSquared) return false; // no intersection

    float offset = MathSqrt(radiusSquared - v3LengthSquared);

    float dist1 = v2Length - offset;
    float dist2 = v2Length + offset;

    Vector3 point1 = origin + dirNorm * dist1;
    Vector3 point2 = origin + dirNorm * dist2;

    Vector3 normal1 = point1 - sphere.position;
    Vector3 normal2 = point2 - sphere.position;

    normal1 = Vector3Normalize(normal1);
    normal2 = Vector3Normalize(normal2);

    Vector3Print(point1);
    Vector3Print(point2);

    cout << dist1 << endl;
    cout << dist2 << endl;

    *outDistance = dist1;
    *outPoint = point1;
    *outNormal = normal1;

    return true;
}
bool Raycast2(Vector3 origin, Vector3 dirNorm, Sphere sphere, float* outDistance, Vector3* outPoint, Vector3* outNormal)
{
    Vector3 diff = origin - sphere.position;

    float b = Vector3Dot(dirNorm, diff) * 2;
    float c = Vector3LengthSquared(diff) - (sphere.radius * sphere.radius);

    float delta = b * b - 4 * c;

    if (delta < 0)
        return false;

    float dist = (-b - MathSqrt(delta)) / 2;

    if (dist < 0)
        return false;

    Vector3 point = origin + dirNorm * dist;
    Vector3 normal = point - sphere.position;

    *outDistance = dist;
    *outPoint = point;
    *outNormal = normal;

    return true;
}