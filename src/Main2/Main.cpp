#include "../Base/Base.h"

int main()
{
    auto mat = MatrixProj2(1,(float)(M_PI_2),0.1f,1000.0f);
    auto mat = MatrixProj3(1,0.1f,1000.0f);
    Matrix mat =
    {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,1,0
    };
    Vector4 v = { 3,4,5,1 };
    Vector4Print(mat * v);
    return 0;
}