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
};
struct Camera
{
    Vector3 position;
    float yaw;
    float pitch;
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
inline Vector3 Vector3Down()
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
    return MathSqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
inline float Vector3LengthNoRoot(Vector3 v)
{
    return v.x*v.x + v.y*v.y + v.z*v.z;
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
inline Vector3 Vector3ClampLength(Vector3 vector, float min, float max)
{
    auto length2 = Vector3Length(vector);
    if (length2 > max) return vector*(max/length2);
    if (length2 < min) return vector*(min/length2);
    return vector;
}
inline Vector3 Vector3Normalize(Vector3 v)
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
inline Vector3 Vector3MoveTowards(Vector3 fromVector, Vector3 toVector, float delta)
{
    if (fromVector == toVector) return fromVector;
    auto diff = toVector-fromVector;
    auto dist = Vector3Length(diff);
    if (dist <= delta) return toVector;
    diff = Vector3Normalize(diff);
    auto moveVec = diff*delta;
    return fromVector+moveVec;
}
inline Vector3 Vector3PositionUpdateSimple(Vector3 position, Vector3 velocity, float deltaTime)
{
    return position + velocity * deltaTime;
}
inline Vector3 Vector3PositionUpdateAdvanced(Vector3 position, Vector3 oldVelocity, Vector3 newVelocity, float deltaTime)
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
    float sin = sinf(rad);
    float cos = cosf(rad);
    return
    {
        1,   0,    0,    0,
        0,   cos,  -sin, 0,
        0,   sin,  cos,  0,
        0,   0,    0,    1
    };
}
inline Matrix MatrixRotateY(float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    return
    {
        cos,   0,  sin,  0,
        0,     1,  0,    0,
        -sin,  0,  cos,  0,
        0,     0,  0,    1
    };
}
inline Matrix MatrixWorld(Vector3 position, Vector3 direction)
{
    Vector3 zaxis = direction;
            zaxis = Vector3Normalize(zaxis);
    Vector3 xaxis = Vector3Cross(Vector3Up(),zaxis);
    Vector3 yaxis = Vector3Cross(zaxis,xaxis);

    return
    {
        xaxis.x, yaxis.x, zaxis.x, position.x,
        xaxis.y, yaxis.y, zaxis.y, position.y,
        xaxis.z, yaxis.z, zaxis.z, position.z,
        0.0f, 0.0f, 0.0f, 1.0f
    };
}
inline Matrix MatrixView(Vector3 eye, float yaw, float pitch)
{
    return
        MatrixRotateX(-pitch) *
        MatrixRotateY(-yaw) *
        MatrixTranslate(-eye);
}
inline Matrix MatrixView(Vector3 eye, Vector3 target, Vector3 up)
{
    Vector3 zaxis = target - eye;
            zaxis = Vector3Normalize(zaxis);

    Vector3 xaxis = Vector3Cross(up,zaxis);
            xaxis = Vector3Normalize(xaxis);

    Vector3 yaxis = Vector3Cross(zaxis,xaxis);

    return
    {
        xaxis.x, xaxis.y, xaxis.z, -Vector3Dot(xaxis, eye),
        yaxis.x, yaxis.y, yaxis.z, -Vector3Dot(yaxis, eye),
        zaxis.x, zaxis.y, zaxis.z, -Vector3Dot(zaxis, eye),
        0.0f, 0.0f, 0.0f, 1.0f
    };
}
inline Matrix MatrixView(const Camera* camera)
{
    return MatrixView(camera->position,camera->yaw,camera->pitch);
}
inline Matrix MatrixProj1(float left, float right, float bottom, float top, float front, float back)
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
inline Matrix MatrixProj2(float aspectRatio, float fovYRadians, float zNear, float zFar)
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
inline Matrix MatrixTransformaton(Matrix model, Matrix view, Matrix proj)
{
    return proj * view * model;
}
void UpdateCameraRotation(Camera* camera, float deltaTime, bool left, bool up, bool down, bool right)
{
    float speed = (float)M_PI; // in radians per second
    float result = speed * deltaTime;
    if(left)   camera->yaw -= result;
    if(up)     camera->pitch -= result;
    if(down)   camera->pitch += result;
    if(right)  camera->yaw += result;

    // Wrap yaw to avoid floating-point errors if we turn too far
    float M_PI2 = 2*(float)M_PI;
    while(camera->yaw >=  M_PI2) camera->yaw -= M_PI2;
    while(camera->yaw <= -M_PI2) camera->yaw += M_PI2;

    // Clamp pitch to stop camera flipping upside down
    float degree = MathToRadians(85);
    if(camera->pitch >  degree) camera->pitch =  degree;
    if(camera->pitch < -degree) camera->pitch = -degree;
}
void UpdateCameraPosition(Camera* camera, float deltaTime, bool w, bool a, bool s, bool d, bool e, bool q)
{
    Matrix matrix = MatrixView(camera);

    Vector3 forward = { matrix.m[2][0], matrix.m[2][1], matrix.m[2][2] };
    Vector3 up = Vector3Up();
    Vector3 right = Vector3Cross(forward, Vector3Up());
            right = Vector3Normalize(right);
            right = -right;

    const float CAM_MOVE_SPEED = 50.0f; // in metres per second
    const float CAM_MOVE_AMOUNT = CAM_MOVE_SPEED * deltaTime;
    if(w) camera->position   += forward * CAM_MOVE_AMOUNT;
    if(s) camera->position   -= forward * CAM_MOVE_AMOUNT;
    if(a) camera->position   -= right * CAM_MOVE_AMOUNT;
    if(d) camera->position   += right * CAM_MOVE_AMOUNT;
    if(e) camera->position.y += CAM_MOVE_AMOUNT;
    if(q) camera->position.y -= CAM_MOVE_AMOUNT;
}
