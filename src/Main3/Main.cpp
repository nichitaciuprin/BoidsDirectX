#include "../Base/Base.h"

int main()
{
    BitmapWindow::Create();

    auto bitmap = make_unique<Bitmap>();

    auto width = BitmapWindow::GetClientWidth();
    auto height = BitmapWindow::GetClientHeight();
    bitmap->Resize(width,height);

    size_t animationIncrement = 0;

    while (BitmapWindow::Exists())
    {
        CheckFPS();

        width = BitmapWindow::GetClientWidth();
        height = BitmapWindow::GetClientHeight();
        bitmap->Resize(width,height);

        bitmap->ScanEffectRandom(animationIncrement);
        animationIncrement++;
        bitmap->DrawSquare(BLACK);
        bitmap->DrawBorder(GREEN);
        BitmapWindow::SetPixels(bitmap->pixels);

        BitmapWindow::Update();
    }

    return 0;
}
