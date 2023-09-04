#include "../Base/Base.h"

int main()
{
    BitmapWindow::Create();

    size_t pixelIndex = 0;
    size_t pixelCount = 1920*1080;
    auto pixels = (uint32_t*)malloc(sizeof(uint32_t)*pixelCount);

    while (BitmapWindow::Exists())
    {
        CheckFPS();

        size_t width;
        size_t height;
        BitmapWindow::GetBitmapInfo(&width, &height);
        ChangePixelsRandomly(pixels, width, height, pixelIndex);
        DrawSquare(pixels, width);
        // Line(0,0,10,10);
        BitmapWindow::SetPixels(pixels);
        pixelIndex++;

        BitmapWindow::Update();
    }

    return 0;
}
