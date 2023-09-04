#include "../Base/Base.h"

int main()
{
    BitmapWindow::Create();

    uint32_t width;
    uint32_t height;
    BitmapWindow::GetBitmapInfo(&width, &height);
    auto bitmap = make_unique<Bitmap>(width,height);

    size_t animationIncrement = 0;

    while (BitmapWindow::Exists())
    {
        CheckFPS();

        bitmap->ScanEffectRandom(animationIncrement);
        bitmap->DrawSquare();
        // Line(0,0,10,10);
        BitmapWindow::SetPixels(bitmap->pixels.data());
        animationIncrement++;

        BitmapWindow::Update();
    }

    return 0;
}
