#include "../Base/Base.h"

int main()
{
    auto width = 400;
    auto height = 400;

    auto bitmap = make_unique<Bitmap>();
    bitmap->Resize(width,height);

    BitmapWindow::Create(700,100,width,height);

    while (true)
    {
        if (!BitmapWindow::Exists()) break;
        CheckFPS();

        bitmap->Clear(BLACK);
        auto position = Vector3Zero();
        auto time = (float)clock()/2000;
        auto t1 = MathSin(time);
        auto t2 = MathCos(time);
        Vector3 direction = {};
        direction += Vector3{t1,0,t2};
        direction += Vector3{t1/2,t2/2,0};
        direction = Vector3Normalize(direction);
        bitmap->DrawCube(position,direction);
        bitmap->DrawBorder(GREEN);

        BitmapWindow::SetPixels(bitmap);

        BitmapWindow::Update();
    }

    return 0;
}
