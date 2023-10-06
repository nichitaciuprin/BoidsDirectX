#include "../Base/Base.h"

int main()
{
    auto width = 400;
    auto height = 400;

    auto bitmap = make_unique<Bitmap>();
    bitmap->Resize(width,height);

    BitmapWindow1::Create(700,100,width,height);

    while (BitmapWindow1::Exists())
    {
        CheckFPS();

        bitmap->Clear(BLACK);
        auto position = Vector3Zero();
        auto offset = Vector3Forward()*6;
        position += offset;
        auto time = (float)clock()/2000;
        auto t1 = MathSin(time);
        auto t2 = MathCos(time);
        Vector3 direction = {};
        direction += Vector3{t1,0,t2};
        direction += Vector3{t1/2,t2/2,0};
        direction = Vector3Normalize(direction);
        bitmap->DrawCube(position,direction);
        bitmap->DrawBorder(GREEN);

        BitmapWindow1::SetPixels(bitmap);

        BitmapWindow1::Update();
    }

    return 0;
}
