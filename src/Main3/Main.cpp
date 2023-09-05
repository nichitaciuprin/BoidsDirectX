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
        animationIncrement++;

        bitmap->DrawSquare(BLACK);
        bitmap->DrawBorder(GREEN);
        BitmapWindow::SetPixels(bitmap->pixels.data());
        BitmapWindow::Update();
    }

    return 0;
}
