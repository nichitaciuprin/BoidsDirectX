// https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/projection-matrix-GPU-rendering-pipeline-clipping.html
// https://carmencincotti.com/2022-11-28/from-clip-space-to-ndc-space/
// https://www.youtube.com/watch?v=pThw0S8MR7w&t=3s
// https://www.youtube.com/watch?v=t7Ztio8cwqM
// https://www.mdpi.com/1999-4893/16/4/201
// https://www.youtube.com/watch?v=4p-E_31XOPM
// https://groups.csail.mit.edu/graphics/classes/6.837/F04/lectures/07_Pipeline_II.pdf
// https://www.youtube.com/watch?v=NYW1TKZG-58&ab_channel=CedricMartens

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
inline float MathSin(float f)
{
    return sinf(f);
}
inline float MathCos(float f)
{
    return cosf(f);
}
inline uint32_t MathMin(uint32_t v1, uint32_t v2)
{
    return min(v1,v2);
}
inline uint32_t MathMax(uint32_t v1, uint32_t v2)
{
    return max(v1,v2);
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
inline void Vector3Print(Vector3 v)
{
    // printf("<%f,%f,%f>",v.x,v.y,v.z);
    cout << "<" << v.x << "," << v.y << "," << v.z << ">" << endl;
}
inline void Vector4Print(Vector4 v)
{
    // printf("<%f,%f,%f,%f>",v.x,v.y,v.z,v.w);
    cout << "<" << v.x << "," << v.y << "," << v.z << "," << v.w << ">" << endl;
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
inline Vector3 operator += (Vector3& left, Vector3 right)
{
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;
    return left;
}
inline Vector3 operator -= (Vector3& left, Vector3 right)
{
    left.x -= right.x;
    left.y -= right.y;
    left.z -= right.z;
    return left;
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
    if (length2 > max) return vector * (max / length2);
    if (length2 < min) return vector * (min / length2);
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
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
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
    return position + (oldVelocity+newVelocity) / 2 * deltaTime;
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
inline Vector3 operator * (Vector3 v, Matrix m)
{
    Vector4 col0 = { m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0] };
    Vector4 col1 = { m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1] };
    Vector4 col2 = { m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2] };

    Vector4 row0 = { v.x, v.y, v.z, 1 };

    float x = Vector4Dot(row0,col0);
    float y = Vector4Dot(row0,col1);
    float z = Vector4Dot(row0,col2);

    return { x, y, z };
}
inline Vector4 operator * (Vector4 v, Matrix m)
{
    Vector4 col0 = { m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0] };
    Vector4 col1 = { m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1] };
    Vector4 col2 = { m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2] };
    Vector4 col3 = { m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3] };

    Vector4 row0 = { v.x, v.y, v.z, 1 };

    float x = Vector4Dot(row0,col0);
    float y = Vector4Dot(row0,col1);
    float z = Vector4Dot(row0,col2);
    float w = Vector4Dot(row0,col3);

    return { x, y, z, w };
}
inline void MatrixPrint(Matrix m)
{
    cout << m.m[0][0] << "," << m.m[0][1] << "," << m.m[0][2] << "," << m.m[0][3] << endl;
    cout << m.m[1][0] << "," << m.m[1][1] << "," << m.m[1][2] << "," << m.m[1][3] << endl;
    cout << m.m[2][0] << "," << m.m[2][1] << "," << m.m[2][2] << "," << m.m[2][3] << endl;
    cout << m.m[3][0] << "," << m.m[3][1] << "," << m.m[3][2] << "," << m.m[3][3] << endl;
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
inline Matrix MatrixTranslate(Vector3 v)
{
    return
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        v.x, v.y, v.z, 1
    };
}
inline Matrix MatrixRotateX(float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    return
    {
        1,   0,    0,    0,
        0,   cos, -sin,  0,
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
        cos,  0,  -sin,  0,
        0,    1,   0,    0,
        sin,  0,   cos,  0,
        0,    0,   0,    1
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
           xaxis.x,    xaxis.y,    xaxis.z,   0.0f,
           yaxis.x,    yaxis.y,    yaxis.z,   0.0f,
           zaxis.x,    zaxis.y,    zaxis.z,   0.0f,
        position.x, position.y, position.z,   1.0f
    };
}
inline Matrix MatrixView(Vector3 eye, float yaw, float pitch)
{
    return
        MatrixTranslate(-eye) *
        MatrixRotateY(-yaw) *
        MatrixRotateX(-pitch);
}
inline Matrix MatrixView(Vector3 eye, Vector3 target, Vector3 up)
{
    Vector3 zaxis = target - eye;
            zaxis = Vector3Normalize(zaxis);

    Vector3 xaxis = Vector3Cross(up, zaxis);
            xaxis = Vector3Normalize(xaxis);

    Vector3 yaxis = Vector3Cross(zaxis, xaxis);

    auto x = -Vector3Dot(xaxis, eye);
    auto y = -Vector3Dot(yaxis, eye);
    auto z = -Vector3Dot(zaxis, eye);

    return
    {
        xaxis.x, xaxis.y, xaxis.z,  0.0f,
        yaxis.x, yaxis.y, yaxis.z,  0.0f,
        zaxis.x, zaxis.y, zaxis.z,  0.0f,
              x,       y,       z,  1.0f
    };
}
inline Matrix MatrixView(const Camera* camera)
{
    return MatrixView(camera->position,camera->yaw,camera->pitch);
}
inline Matrix MatrixOrthographic(float width, float height, float zNear, float zFar)
{
    float w = 2.0f / width;
    float h = 2.0f / height;
    float a = 1.0f / (zFar - zNear);
    float b = -a * zNear;
    return
    {
        w, 0, 0, 0,
        0, h, 0, 0,
        0, 0, a, 0,
        0, 0, b, 1
    };
}
inline Matrix MatrixPerspective(float width, float height, float zNear, float zFar)
{
    float aspectRatio = width / height;
    float fov = (float)(M_PI_2); // 90 degree
    float h = 1.0f / tanf(fov / 2);
    float w = h / aspectRatio;
    float a = zFar / (zFar - zNear);
    float b = (-zNear * zFar) / (zFar - zNear);
    return
    {
        w, 0, 0, 0,
        0, h, 0, 0,
        0, 0, a, 1,
        0, 0, b, 0
    };
}
void UpdateCameraRotation(Camera* camera, float deltaTime, bool left, bool up, bool down, bool right)
{
    float speed = (float)M_PI;
    float speedDelta = speed * deltaTime;
    if (up)    camera->pitch += speedDelta;
    if (down)  camera->pitch -= speedDelta;
    if (right) camera->yaw   += speedDelta;
    if (left)  camera->yaw   -= speedDelta;

    // TODO review
    // Wrap yaw to avoid floating-point errors if we turn too far
    float M_PI2 = 2*(float)M_PI;
    while (camera->yaw >=  M_PI2) camera->yaw -= M_PI2;
    while (camera->yaw <= -M_PI2) camera->yaw += M_PI2;

    // Clamp pitch to stop camera flipping upside down
    float degree = MathToRadians(85);
    if (camera->pitch >  degree) camera->pitch =  degree;
    if (camera->pitch < -degree) camera->pitch = -degree;
}
void UpdateCameraPosition(Camera* camera, float deltaTime, bool w, bool a, bool s, bool d, bool e, bool q)
{
    Matrix matrix = MatrixView(camera);

    Vector3 forward = { matrix.m[0][2], matrix.m[1][2], matrix.m[2][2] };
    Vector3 up = Vector3Up();
    Vector3 right = Vector3Cross(up,forward);

    auto speed = 50.0f;
    auto speedDelta = speed * deltaTime;

    if (w) camera->position += forward * speedDelta;
    if (s) camera->position -= forward * speedDelta;
    if (d) camera->position += right   * speedDelta;
    if (a) camera->position -= right   * speedDelta;
    if (e) camera->position += up      * speedDelta;
    if (q) camera->position -= up      * speedDelta;
}

// TODO review
inline Matrix MatrixProj2(float aspectRatio, float fovYRadians, float zNear, float zFar)
{

    float yScale = tanf(0.5f * ((float)M_PI - fovYRadians));
    float xScale = yScale / aspectRatio;
    float zRangeInverse = 1.0f / (zNear - zFar);
    float zScale = zFar * zRangeInverse;
    float zTranslation = zFar * zNear * zRangeInverse;
    return
    {
        xScale, 0, 0, 0,
        0, yScale, 0, 0,
        0, 0, zScale, -zTranslation,
        0, 0, 1, 0
    };
}