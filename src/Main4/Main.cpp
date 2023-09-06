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
        // bitmap->DrawX(RED);
        // bitmap->DrawCross(BLUE);

        uint32_t outX0, outY0; Vector2 v0 = {};
        uint32_t outX1, outY1; Vector2 v1 = {};
        v1.x = 1; v1.y = 1;
        bitmap->ToScreenSpace(v0,&outX0,&outY0);
        bitmap->ToScreenSpace(v1,&outX1,&outY1);

        bitmap->DrawLine(outX0,outY0,outX1,outY1,BLUE);
        // bitmap->DrawLine(150,150,200,150,BLUE);

        bitmap->DrawBorder(GREEN);
        BitmapWindow::SetPixels2(bitmap);
        BitmapWindow::Update();
    }

    return 0;
}
