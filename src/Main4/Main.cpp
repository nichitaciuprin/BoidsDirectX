#include "../Base/Base.h"

int main()
{
    auto width = 401;
    auto height = 401;

    auto bitmap = make_unique<Bitmap>();
    bitmap->Resize(width,height);

    BitmapWindow::Create(700,0,width,height);

    while (BitmapWindow::Exists())
    {
        CheckFPS();
        bitmap->Clear(BLACK);

        auto position = Vector3Zero();
        auto time = (float)clock()/400;
        auto t1 = MathSin(time);
        auto t2 = MathCos(time);
        Vector3 direction = {};
        direction += Vector3{t1,0,t2};
        direction += Vector3{t1/2,t2/2,0};
        direction = Vector3Normalize(direction);
        bitmap->DrawCube(Vector3Zero(),direction);

        bitmap->DrawBorder(GREEN);
        BitmapWindow::SetPixels2(bitmap);
        BitmapWindow::Update();
    }

    return 0;
}
