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
union Matrix
{
    float m[4][4];
    Vector4 cols[4];
    inline Vector4 row(int i)
    {
        return { m[0][i], m[1][i], m[2][i], m[3][i] };
    }
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
Vector3 Vector3Zero()
{
    return { 0, 0, 0 };
}
Vector3 Vector3Left()
{
    return { -1, 0, 0 };
}
Vector3 Vector3Right()
{
    return { 1, 0, 0 };
}
Vector3 Vector3Up()
{
    return { 0, 1, 0 };
}
Vector3 Vector3Forward()
{
    return { 0, 0, -1 };
}
Vector3 Vector3Backward()
{
    return { 0, 0, 1 };
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
inline Vector3 Cross(Vector3 a, Vector3 b)
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
    return
    {
        Vector4Dot(a.row(0), b.cols[0]),
        Vector4Dot(a.row(1), b.cols[0]),
        Vector4Dot(a.row(2), b.cols[0]),
        Vector4Dot(a.row(3), b.cols[0]),
        Vector4Dot(a.row(0), b.cols[1]),
        Vector4Dot(a.row(1), b.cols[1]),
        Vector4Dot(a.row(2), b.cols[1]),
        Vector4Dot(a.row(3), b.cols[1]),
        Vector4Dot(a.row(0), b.cols[2]),
        Vector4Dot(a.row(1), b.cols[2]),
        Vector4Dot(a.row(2), b.cols[2]),
        Vector4Dot(a.row(3), b.cols[2]),
        Vector4Dot(a.row(0), b.cols[3]),
        Vector4Dot(a.row(1), b.cols[3]),
        Vector4Dot(a.row(2), b.cols[3]),
        Vector4Dot(a.row(3), b.cols[3]),
    };
}
inline Matrix Identity()
{
    return
    {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1,
    };
}
inline Matrix RotateXMatrix(float rad)
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
inline Matrix RotateYMatrix(float rad)
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
inline Matrix TranslationMatrix(Vector3 trans)
{
    return {
        1, 0, 0, trans.x,
        0, 1, 0, trans.y,
        0, 0, 1, trans.z,
        0, 0, 0, 1
    };
}
inline Matrix MakePerspectiveMat(float aspectRatio, float fovYRadians, float zNear, float zFar)
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
        0, 0, zScale, zTranslation,
        0, 0, -1, 0
    };
    return result;
}
Matrix ToViewMatrix(Vector3 position, float rot1, float ro2)
{
    return
        TranslationMatrix(-position) *
        RotateYMatrix(rot1) *
        RotateXMatrix(ro2);
}
Matrix ToViewMatrix(const Camera* camera)
{
    return
        TranslationMatrix(-camera->position) *
        RotateYMatrix(camera->rot1) *
        RotateXMatrix(camera->rot2);
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
    Matrix viewMatrix = ToViewMatrix(camera);
    Vector3 camFwdXZ = {-viewMatrix.m[2][0], -viewMatrix.m[2][1], -viewMatrix.m[2][2]};

    // Vector3 camFwdXZ = Normalise({camera->cameraFwd.x, 0, camera->cameraFwd.z});
    Vector3 cameraRightXZ = Cross(camFwdXZ, {0, 1, 0});

    const float CAM_MOVE_SPEED = 5.f; // in metres per second
    const float CAM_MOVE_AMOUNT = CAM_MOVE_SPEED * deltaTime;
    if(w) camera->position   += camFwdXZ * CAM_MOVE_AMOUNT;
    if(s) camera->position   -= camFwdXZ * CAM_MOVE_AMOUNT;
    if(a) camera->position   -= cameraRightXZ * CAM_MOVE_AMOUNT;
    if(d) camera->position   += cameraRightXZ * CAM_MOVE_AMOUNT;
    if(e) camera->position.y += CAM_MOVE_AMOUNT;
    if(q) camera->position.y -= CAM_MOVE_AMOUNT;
}
Matrix MatrixLookAt1(Vector3 eye, Vector3 target, Vector3 up)
{
    // TODO. Needs tests. Taken from raylib.

    Matrix result = { 0 };

    float length = 0.0f;
    float ilength = 0.0f;

    // Vector3Subtract(eye, target)
    Vector3 vz = { eye.x - target.x, eye.y - target.y, eye.z - target.z };

    // Vector3Normalize(vz)
    Vector3 v = vz;
    length = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
    if (length == 0.0f) length = 1.0f;
    ilength = 1.0f/length;
    vz.x *= ilength;
    vz.y *= ilength;
    vz.z *= ilength;

    // Vector3CrossProduct(up, vz)
    Vector3 vx = { up.y*vz.z - up.z*vz.y, up.z*vz.x - up.x*vz.z, up.x*vz.y - up.y*vz.x };

    // Vector3Normalize(x)
    v = vx;
    length = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
    if (length == 0.0f) length = 1.0f;
    ilength = 1.0f/length;
    vx.x *= ilength;
    vx.y *= ilength;
    vx.z *= ilength;

    // Vector3CrossProduct(vz, vx)
    Vector3 vy = { vz.y*vx.z - vz.z*vx.y, vz.z*vx.x - vz.x*vx.z, vz.x*vx.y - vz.y*vx.x };

    result.m0 = vx.x;
    result.m1 = vy.x;
    result.m2 = vz.x;
    result.m3 = 0.0f;
    result.m4 = vx.y;
    result.m5 = vy.y;
    result.m6 = vz.y;
    result.m7 = 0.0f;
    result.m8 = vx.z;
    result.m9 = vy.z;
    result.m10 = vz.z;
    result.m11 = 0.0f;
    result.m12 = -(vx.x*eye.x + vx.y*eye.y + vx.z*eye.z);   // Vector3DotProduct(vx, eye)
    result.m13 = -(vy.x*eye.x + vy.y*eye.y + vy.z*eye.z);   // Vector3DotProduct(vy, eye)
    result.m14 = -(vz.x*eye.x + vz.y*eye.y + vz.z*eye.z);   // Vector3DotProduct(vz, eye)
    result.m15 = 1.0f;

    return result;
}
Matrix MatrixLookAt2(Vector3 eye, Vector3 target, Vector3 up)
{
    // TODO. Needs tests. Taken from https://www.geertarien.com/blog/2017/07/30/breakdown-of-the-lookAt-function-in-OpenGL/

    vec3 zaxis = Normalise(target - eye);
    vec3 xaxis = Normalise(Cross(zaxis, up));
    vec3 yaxis = cross(xaxis, zaxis);
    zaxis = -zaxis;
    return
    {
        xaxis.x, xaxis.y, xaxis.z, -dot(xaxis, eye)
        yaxis.x, yaxis.y, yaxis.z, -dot(yaxis, eye)
        zaxis.x, zaxis.y, zaxis.z, -dot(zaxis, eye)
        0, 0, 0, 1
    };
}
Matrix MatrixLookAt3(Vector3 eye, Vector3 target, Vector3 up)
{
    // TODO. Needs tests. Taken from raylib.

    Vector3 vz = eye - target;
    vz = Normalise(vz);
    Vector3 vx = Cross(up,vz);
    vx = Normalise(vx);
    Vector3 vy = Cross(vz,vx);

    return Matrix
    {
        vx.x, vx.y, vx.z, -Vector3Dot(vx,eye),
        vy.x, vy.y, vy.z, -Vector3Dot(vy,eye),
        vz.x, vz.y, vz.z, -Vector3Dot(vz,eye),
        0.0f, 0.0f, 0.0f, 1.0f
    };

    return result;
}