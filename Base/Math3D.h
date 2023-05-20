#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

struct float2
{
    float x, y;
};
struct float3
{
    float x, y, z;
};
struct float4
{
    float x, y, z, w;
};
union float4x4
{
    float m[4][4];
    float4 cols[4];
    inline float4 row(int i)
    {
        return { m[0][i], m[1][i], m[2][i], m[3][i] };
    }
};
struct Camera
{
    float3 cameraPos;
    float rot1;
    float rot2;
};

inline float degreesToRadians(float degs)
{
    return degs * ((float)M_PI / 180.0f);
}
inline float length(float3 v)
{
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}
inline float dot(float4 a, float4 b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}
inline float3 operator* (float3 v, float f)
{
    return {v.x*f, v.y*f, v.z*f};
}
inline float3 normalise(float3 v)
{
    return v * (1.f / length(v));
}
inline float3 cross(float3 a, float3 b)
{
    return
    {
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    };
}
inline float3 operator+= (float3 &lhs, float3 rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    return lhs;
}
inline float3 operator-= (float3 &lhs, float3 rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
    return lhs;
}
inline float3 operator- (float3 v)
{
    return {-v.x, -v.y, -v.z};
}
inline float4x4 rotateXMat(float rad)
{
    float sinTheta = sinf(rad);
    float cosTheta = cosf(rad);
    return {
        1, 0, 0, 0,
        0, cosTheta, -sinTheta, 0,
        0, sinTheta, cosTheta, 0,
        0, 0, 0, 1
    };
}
inline float4x4 rotateYMat(float rad)
{
    float sinTheta = sinf(rad);
    float cosTheta = cosf(rad);
    return {
        cosTheta, 0, sinTheta, 0,
        0, 1, 0, 0,
        -sinTheta, 0, cosTheta, 0,
        0, 0, 0, 1
    };
}
inline float4x4 translationMat(float3 trans)
{
    return {
        1, 0, 0, trans.x,
        0, 1, 0, trans.y,
        0, 0, 1, trans.z,
        0, 0, 0, 1
    };
}
inline float4x4 makePerspectiveMat(float aspectRatio, float fovYRadians, float zNear, float zFar)
{
    float yScale = tanf(0.5f * ((float)M_PI - fovYRadians));
    float xScale = yScale / aspectRatio;
    float zRangeInverse = 1.f / (zNear - zFar);
    float zScale = zFar * zRangeInverse;
    float zTranslation = zFar * zNear * zRangeInverse;
    float4x4 result =
    {
        xScale, 0, 0, 0,
        0, yScale, 0, 0,
        0, 0, zScale, zTranslation,
        0, 0, -1, 0
    };
    return result;
}
inline float4x4 operator* (float4x4 a, float4x4 b)
{
    return
    {
        dot(a.row(0), b.cols[0]),
        dot(a.row(1), b.cols[0]),
        dot(a.row(2), b.cols[0]),
        dot(a.row(3), b.cols[0]),
        dot(a.row(0), b.cols[1]),
        dot(a.row(1), b.cols[1]),
        dot(a.row(2), b.cols[1]),
        dot(a.row(3), b.cols[1]),
        dot(a.row(0), b.cols[2]),
        dot(a.row(1), b.cols[2]),
        dot(a.row(2), b.cols[2]),
        dot(a.row(3), b.cols[2]),
        dot(a.row(0), b.cols[3]),
        dot(a.row(1), b.cols[3]),
        dot(a.row(2), b.cols[3]),
        dot(a.row(3), b.cols[3]),
    };
}
float4x4 ToViewMatrix(const Camera* camera)
{
    return
        translationMat(-camera->cameraPos) *
        rotateYMat(camera->rot1) *
        rotateXMat(camera->rot2);
}
void UpdateCameraRotation(Camera* camera, float deltaTime, bool left, bool up, bool down, bool right)
{
    float speed = (float)M_PI; // in radians per second
    float result = speed * deltaTime;
    if(left)   camera->rot1 -= result;
    if(up)     camera->rot2 -= result;
    if(down)   camera->rot2 += result;
    if(right)  camera->rot1 += result;

    // Wrap yaw to avoid floating-point errors if we turn too far
    float M_PI2 = 2*(float)M_PI;
    while(camera->rot1 >=  M_PI2) camera->rot1 -= M_PI2;
    while(camera->rot1 <= -M_PI2) camera->rot1 += M_PI2;

    // Clamp pitch to stop camera flipping upside down
    float degree = degreesToRadians(85);
    if(camera->rot2 >  degree) camera->rot2 =  degree;
    if(camera->rot2 < -degree) camera->rot2 = -degree;
}
void UpdateCameraPosition(Camera* camera, float deltaTime, bool w, bool a, bool s, bool d, bool e, bool q)
{
    float4x4 viewMatrix = ToViewMatrix(camera);
    float3 camFwdXZ = {-viewMatrix.m[2][0], -viewMatrix.m[2][1], -viewMatrix.m[2][2]};

    // float3 camFwdXZ = normalise({camera->cameraFwd.x, 0, camera->cameraFwd.z});
    float3 cameraRightXZ = cross(camFwdXZ, {0, 1, 0});

    const float CAM_MOVE_SPEED = 5.f; // in metres per second
    const float CAM_MOVE_AMOUNT = CAM_MOVE_SPEED * deltaTime;
    if(w) camera->cameraPos   += camFwdXZ * CAM_MOVE_AMOUNT;
    if(s) camera->cameraPos   -= camFwdXZ * CAM_MOVE_AMOUNT;
    if(a) camera->cameraPos   -= cameraRightXZ * CAM_MOVE_AMOUNT;
    if(d) camera->cameraPos   += cameraRightXZ * CAM_MOVE_AMOUNT;
    if(e) camera->cameraPos.y += CAM_MOVE_AMOUNT;
    if(q) camera->cameraPos.y -= CAM_MOVE_AMOUNT;
}