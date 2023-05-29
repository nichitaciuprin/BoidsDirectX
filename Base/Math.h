#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

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
    // float m0,m1,m2,m3;
    // float m4,m5,m6,m7;
    // float m8,m9,m10,m11;
    // float m12,m13,m14,m15;
};
struct Camera
{
    Vector3 position;
    float rot1;
    float rot2;
};
inline int MathSign(float value)
{
    if (value > 0) { return  1; }
    if (value < 0) { return -1; }
                     return  0;
}
inline float MathMin(float value1, float value2)
{
    return fminf(value1,value2);
}
inline float MathMax(float value1, float value2)
{
    return fmaxf(value1, value2);
}
inline float MathAbs(float value)
{
    return fabsf(value);
}
inline float MathSqrt(float value)
{
    return sqrtf(value);
}
inline float MathClamp(float value, float min, float max)
{
    if (value < min) { return min; };
    if (value > max) { return max; };
                       return value;
}
inline float MathInverseLerp(float x, float y, float value)
{
    return (value - x)/(y - x);
}
inline float MathMod(float value, float div)
{
    return fmodf(value,div);
}
inline float MathPingPong(float value, float length)
{
    value = MathAbs(value);
    int whole = (int)(value/length);
    float rem = fmodf(value,length);
    return whole % 2 == 0 ? rem : length-rem;
}
inline float MathToRadians(float degs)
{
    return degs * ((float)M_PI / 180.0f);
}
inline Vector3 Vector3Zero()
{
    return { 0, 0, 0 };
}
inline Vector3 Vector3Left()
{
    return { -1, 0, 0 };
}
inline Vector3 Vector3Right()
{
    return { 1, 0, 0 };
}
inline Vector3 Vector3Up()
{
    return { 0, 1, 0 };
}
inline Vector3 Vector3Forward()
{
    return { 0, 0, 1 };
}
inline Vector3 Vector3Backward()
{
    return { 0, 0, -1 };
}
inline float Vector3Length(Vector3 v)
{
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}
inline float Vector3Dot(Vector3 a, Vector3 b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
inline float Vector4Dot(Vector4 a, Vector4 b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}
inline bool operator == (Vector3 left, Vector3 right)
{
    if (left.x != right.x) return false;
    if (left.y != right.y) return false;
    if (left.z != right.z) return false;
                           return true;
}
inline Vector3 operator - (Vector3 v)
{
    return {-v.x, -v.y, -v.z};
}
inline Vector3 operator + (Vector3 left, Vector3 right)
{
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;
    return left;
}
inline Vector3 operator - (Vector3 left, Vector3 right)
{
    left.x -= right.x;
    left.y -= right.y;
    left.z -= right.z;
    return left;
}
inline Vector3 operator * (Vector3 v, float f)
{
    v.x *= f;
    v.y *= f;
    v.z *= f;
    return v;
}
inline Vector3 operator / (Vector3 v, float f)
{
    v.x /= f;
    v.y /= f;
    v.z /= f;
    return v;
}
inline Vector3 operator += (Vector3 &lhs, Vector3 rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    return lhs;
}
inline Vector3 operator -= (Vector3 &lhs, Vector3 rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
    return lhs;
}
inline Vector3 operator *= (Vector3& v, float f)
{
    v.x *= f;
    v.y *= f;
    v.z *= f;
    return v;
}
inline Vector3 operator /= (Vector3& v, float f)
{
    v.x /= f;
    v.y /= f;
    v.z /= f;
    return v;
}
inline Vector3 ClampLength(Vector3 vector, float min, float max)
{
    auto length2 = Vector3Length(vector);
    if (length2 > max) return vector*(max/length2);
    if (length2 < min) return vector*(min/length2);
    return vector;
}
inline Vector3 Normalise(Vector3 v)
{
    return v * (1.f / Vector3Length(v));
}
inline Vector3 Vector3Cross(Vector3 a, Vector3 b)
{
    return
    {
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    };
}
inline Vector3 MoveTowards(Vector3 fromVector, Vector3 toVector, float delta)
{
    if (fromVector == toVector) return fromVector;
    auto diff = toVector-fromVector;
    auto dist = Vector3Length(diff);
    if (dist <= delta) return toVector;
    diff = Normalise(diff);
    auto moveVec = diff*delta;
    return fromVector+moveVec;
}
inline Vector3 PositionUpdateSimple(Vector3 position, Vector3 velocity, float deltaTime)
{
    return position + velocity * deltaTime;
}
inline Vector3 PositionUpdateAdvanced(Vector3 position, Vector3 oldVelocity, Vector3 newVelocity, float deltaTime)
{
    return position + (oldVelocity+newVelocity)/2 * deltaTime;
}
inline Matrix operator * (Matrix a, Matrix b)
{
    Vector4 row0 = { a.m[0][0], a.m[0][1], a.m[0][2], a.m[0][3] };
    Vector4 row1 = { a.m[1][0], a.m[1][1], a.m[1][2], a.m[1][3] };
    Vector4 row2 = { a.m[2][0], a.m[2][1], a.m[2][2], a.m[2][3] };
    Vector4 row3 = { a.m[3][0], a.m[3][1], a.m[3][2], a.m[3][3] };

    Vector4 col0 = { b.m[0][0], b.m[1][0], b.m[2][0], b.m[3][0] };
    Vector4 col1 = { b.m[0][1], b.m[1][1], b.m[2][1], b.m[3][1] };
    Vector4 col2 = { b.m[0][2], b.m[1][2], b.m[2][2], b.m[3][2] };
    Vector4 col3 = { b.m[0][3], b.m[1][3], b.m[2][3], b.m[3][3] };

    float m00 = Vector4Dot(row0,col0);
    float m01 = Vector4Dot(row0,col1);
    float m02 = Vector4Dot(row0,col2);
    float m03 = Vector4Dot(row0,col3);

    float m10 = Vector4Dot(row1,col0);
    float m11 = Vector4Dot(row1,col1);
    float m12 = Vector4Dot(row1,col2);
    float m13 = Vector4Dot(row1,col3);

    float m20 = Vector4Dot(row2,col0);
    float m21 = Vector4Dot(row2,col1);
    float m22 = Vector4Dot(row2,col2);
    float m23 = Vector4Dot(row2,col3);

    float m30 = Vector4Dot(row3,col0);
    float m31 = Vector4Dot(row3,col1);
    float m32 = Vector4Dot(row3,col2);
    float m33 = Vector4Dot(row3,col3);

    Matrix result =
    {
        m00,m01,m02,m03,
        m10,m11,m12,m13,
        m20,m21,m22,m23,
        m30,m31,m32,m33
    };

    return result;
}
inline Matrix MatrixIdentity()
{
    return
    {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1,
    };
}
inline Matrix MatrixTranspose(Matrix a)
{
    return Matrix
    {
        a.m[0][0],a.m[1][0],a.m[2][0],a.m[3][0],
        a.m[0][1],a.m[1][1],a.m[2][1],a.m[3][1],
        a.m[0][2],a.m[1][2],a.m[2][2],a.m[3][2],
        a.m[0][3],a.m[1][3],a.m[2][3],a.m[3][3]
    };
}
inline Matrix MatrixTranslate(Vector3 trans)
{
    return
    {
        1, 0, 0, trans.x,
        0, 1, 0, trans.y,
        0, 0, 1, trans.z,
        0, 0, 0, 1
    };
}
inline Matrix MatrixRotateX(float rad)
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
inline Matrix MatrixRotateY(float rad)
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
inline Matrix MatrixOrtho(float left, float right, float bottom, float top, float front, float back)
{
    float rl = right - left;
    float tb = top - bottom;
    float fn = back - front;

    float sx = 2.0f/rl;
    float sy = 2.0f/tb;
    float sz = -2.0f/fn;

    float x = -(left + right)  / rl;
    float y = -(top  + bottom) / tb;
    float z = -(back + front)  / fn;

    return
    {
        sx, 0 , 0,  x,
        0 , sy, 0,  y,
        0 , 0 , sz, z,
        0 , 0 , 0,  1
    };
}
inline Matrix MatrixPerspective(float aspectRatio, float fovYRadians, float zNear, float zFar)
{
    float yScale = tanf(0.5f * ((float)M_PI - fovYRadians));
    float xScale = yScale / aspectRatio;
    float zRangeInverse = 1.f / (zNear - zFar);
    float zScale = zFar * zRangeInverse;
    float zTranslation = zFar * zNear * zRangeInverse;
    Matrix result =
    {
        xScale, 0, 0, 0,
        0, yScale, 0, 0,
        0, 0, zScale, -zTranslation,
        0, 0, 1, 0
    };
    return result;
}
inline Matrix MatrixView(Vector3 position, float rot1, float ro2)
{
    return
        MatrixTranslate(-position) *
        MatrixRotateY(rot1) *
        MatrixRotateX(ro2);
}
inline Matrix MatrixView(const Camera* camera)
{
    return
        MatrixTranslate(-camera->position) *
        MatrixRotateY(camera->rot1) *
        MatrixRotateX(camera->rot2);
}
inline Matrix MatrixView(Vector3 eye, Vector3 target, Vector3 up)
{
    // Taken from https://www.geertarien.com/blog/2017/07/30/breakdown-of-the-lookAt-function-in-OpenGL/
    Vector3 zaxis = Normalise(target - eye);
    Vector3 xaxis = Normalise(Vector3Cross(zaxis, up));
    Vector3 yaxis =           Vector3Cross(xaxis, zaxis);
    // zaxis = -zaxis;
    return
    {
        xaxis.x, xaxis.y, xaxis.z, -Vector3Dot(xaxis, eye),
        yaxis.x, yaxis.y, yaxis.z, -Vector3Dot(yaxis, eye),
        zaxis.x, zaxis.y, zaxis.z, -Vector3Dot(zaxis, eye),
        0.0f, 0.0f, 0.0f, 1.0f
    };
}
inline Matrix MatrixView2(Vector3 eye, Vector3 target, Vector3 up)
{
    Vector3 vz = eye - target;
    vz = Normalise(vz);
    Vector3 vx = Vector3Cross(up,vz);
    vx = Normalise(vx);
    Vector3 vy = Vector3Cross(vz,vx);

    return Matrix
    {
        vx.x, vx.y, vx.z, -Vector3Dot(vx,eye),
        vy.x, vy.y, vy.z, -Vector3Dot(vy,eye),
        vz.x, vz.y, vz.z, -Vector3Dot(vz,eye),
        0.0f, 0.0f, 0.0f, 1.0f
    };
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
    float degree = MathToRadians(85);
    if(camera->rot2 >  degree) camera->rot2 =  degree;
    if(camera->rot2 < -degree) camera->rot2 = -degree;
}
void UpdateCameraPosition(Camera* camera, float deltaTime, bool w, bool a, bool s, bool d, bool e, bool q)
{
    Matrix viewMatrix = MatrixView(camera);
    Vector3 camFwdXZ = {-viewMatrix.m[2][0], -viewMatrix.m[2][1], -viewMatrix.m[2][2]};

    // Vector3 camFwdXZ = Normalise({camera->cameraFwd.x, 0, camera->cameraFwd.z});
    Vector3 cameraRightXZ = Vector3Cross(camFwdXZ, {0, 1, 0});

    const float CAM_MOVE_SPEED = 5.f; // in metres per second
    const float CAM_MOVE_AMOUNT = CAM_MOVE_SPEED * deltaTime;
    if(w) camera->position   += camFwdXZ * CAM_MOVE_AMOUNT;
    if(s) camera->position   -= camFwdXZ * CAM_MOVE_AMOUNT;
    if(a) camera->position   -= cameraRightXZ * CAM_MOVE_AMOUNT;
    if(d) camera->position   += cameraRightXZ * CAM_MOVE_AMOUNT;
    if(e) camera->position.y += CAM_MOVE_AMOUNT;
    if(q) camera->position.y -= CAM_MOVE_AMOUNT;
}
