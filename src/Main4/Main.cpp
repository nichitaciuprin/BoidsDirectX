#include "../Base/Base.h"

int main()
{
    auto width = 400;
    auto height = 400;

    auto bitmap = make_unique<Bitmap>(width, height);

    BitmapWindow1::Create(700, 100, width, height);

    while (BitmapWindow1::Exists())
    {
        CheckFPS();

        bitmap->Fill(BLACK);
        auto position = Vector3Zero();
        // position += Vector3Forward() * 2;
        auto time = (float)clock() / 4000;
        auto t1 = MathSin(time);
        auto t2 = MathCos(time);
        Vector3 direction = {};
        direction += Vector3{t1, 0, t2} * 2;
        // direction += Vector3{t1/2, t2/2, 0};
        direction = Vector3Normalize(direction);
        bitmap->DrawCube(position, direction);
        bitmap->DrawBorder(GREEN);

        BitmapWindow1::SetPixels(bitmap);

        BitmapWindow1::Update();
    }

    return 0;
}
