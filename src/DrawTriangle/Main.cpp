#include "../Base/Base.h"

void main2()
{
    auto width = 400;
    auto height = 400;

    auto bitmap = make_unique<Bitmap>(width, height);

    BitmapWindow1::Create(700, 100, width, height);

    while (BitmapWindow1::Exists())
    {
        // CheckFPS();
        bitmap->Fill(BLACK);

        // int height = 300

        {
            // int x0 = 200; int y0 = 50;
            // int x1 = 150; int y1 = 100;
            // int x2 = 250; int y2 = 150;
            // bitmap->DrawTriangle(x0, y0, x1, y1, x2, y2, GREEN);
        }
        {
            int x0 = 200; int y0 = 50;
            int x1 = 150; int y1 = 100;
            int x2 = 225; int y2 = 100;
            bitmap->DrawTriangleTop(x0, y0, x1, y1, x2, y2, GREEN);
        }
        {
            int x0 = 250; int y0 = 150;
            int x1 = 150; int y1 = 100;
            int x2 = 225; int y2 = 100;
            bitmap->DrawTriangleBottom(x0, y0, x1, y1, x2, y2, GREEN);
        }

        bitmap->DrawBorder(GREEN);
        BitmapWindow1::SetPixels(bitmap);
        BitmapWindow1::Update();
    }
}

int main()
{
    try
    {
        main2();
    }
    catch (const exception& e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}