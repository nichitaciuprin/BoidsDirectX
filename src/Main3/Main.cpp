#include "../Base/Base.h"

int main()
{
    BitmapWindow::Create();

    auto width = BitmapWindow::GetClientWidth();
    auto height = BitmapWindow::GetClientHeight();
    auto bitmap = make_unique<Bitmap>(width,height);

    size_t animationIncrement = 0;

    while (BitmapWindow::Exists())
    {
        CheckFPS();

        bitmap->ScanEffectRandom(animationIncrement);
        bitmap->DrawSquare(BLACK);

        bitmap->DrawLine(0      ,0       ,0      ,height-1,GREEN);
        bitmap->DrawLine(0      ,0       ,width-1,0       ,GREEN);
        bitmap->DrawLine(width-1,height-1,width-1,0       ,GREEN);
        bitmap->DrawLine(width-1,height-1,0      ,height-1,GREEN);

        // bitmap->DrawLine(0,0,width-1,height-1,RED);
        // bitmap->DrawLine(width-1,0,0,height-1,RED);

        BitmapWindow::SetPixels(bitmap->pixels.data());
        animationIncrement++;

        BitmapWindow::Update();
    }

    return 0;
}
