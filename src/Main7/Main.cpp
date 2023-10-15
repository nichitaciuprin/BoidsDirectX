#include "../Base/Base.h"

void main2()
{
    // Vector3 from = { 0, 0, 0 };
    // Vector3 dir = { 0, 0, 1 };
    // dir = Vector3Normalize(dir);
    // Sphere sphere = { { 0, 0, 101 }, 1.0f };
    // float outDistance = 0;
    // Vector3 outPoint = {};
    // Vector3 outNormal = {};
    // auto isHit = Raycast2(from, dir, sphere, &outDistance, &outPoint, &outNormal);
    // cout << isHit << endl;
    // cout << outDistance << endl;

    Vector3 from = { 0, 0, 0 };
    Vector3 dir = { 1, 0, 1 };
    dir = Vector3Normalize(dir);
    Sphere sphere = { { 101, 0, 101 }, 1.0f };
    auto isHit = Raycast(from, dir, sphere);
    cout << isHit << endl;

    // Vector3 start = { 0, 0, 0 };
    // Vector3 end = { 0, 0, 100.0f };
    // Sphere sphere = { { 0.0f, 0, 102 }, 1.0f };
    // auto isHit = RaycastLine(start, end, sphere);
    // cout << isHit << endl;
}

int main()
{
    try
    {
        main2();
    }
    catch (const exception& e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}