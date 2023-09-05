#include "../Base/Base.h"

int main()
{
    BitmapWindow::Create(400,300);
    auto width = BitmapWindow::GetClientWidth();
    auto height = BitmapWindow::GetClientHeight();

    auto bitmap = make_unique<Bitmap>();
    bitmap->Resize(width,height);

    size_t animationIteration = 0;

    while (BitmapWindow::Exists())
    {
        CheckFPS();

        bitmap->ScanEffectRandom(animationIteration);
        animationIteration++;
        bitmap->DrawBorder(GREEN);

        BitmapWindow::SetPixels2(bitmap);

        BitmapWindow::Update();
    }

    return 0;
}
