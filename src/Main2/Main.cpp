#include "../Base/Base.h"

int main()
{
    Vector4 v = { 0,0,0.0001f,0 };

    float zFar = 100.0f;
    float zNear = 10.0f;
    auto mat = MatrixPerspective(1.0f,1.0f,zNear,zFar);

    v = v * mat; Vector4Print(v);
    v = v / v.w; Vector4Print(v);

    return 0;
}