#include "../Base/Base.h"

int main()
{
    BitmapWindow::Create(700,0,40,400);
    auto width = BitmapWindow::GetClientWidth();
    auto height = BitmapWindow::GetClientHeight();

    auto bitmap = make_unique<Bitmap>();
    bitmap->Resize(width,height);

    while (BitmapWindow::Exists())
    {
        CheckFPS();
        bitmap->DrawBorder(GREEN);
        BitmapWindow::SetPixels2(bitmap);
        BitmapWindow::Update();
    }

    return 0;
}
