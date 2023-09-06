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

        bitmap->DrawCube(Vector3Zero());

        bitmap->DrawBorder(GREEN);
        BitmapWindow::SetPixels2(bitmap);
        BitmapWindow::Update();
    }

    return 0;
}
