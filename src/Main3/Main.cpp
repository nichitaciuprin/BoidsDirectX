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

        // bitmap->ScanEffectRandom(animationIncrement);
        bitmap->DrawSquare(BLUE);
        bitmap->DrawLine(0,0,width-1,height-1,RED);
        BitmapWindow::SetPixels(bitmap->pixels.data());
        animationIncrement++;

        BitmapWindow::Update();
    }

    return 0;
}
