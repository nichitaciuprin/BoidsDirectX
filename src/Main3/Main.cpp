#include "../Base/Base.h"

void ChangePixelsRandomly(uint32_t* pixels, size_t width, size_t height, size_t pixelIndex)
{
    size_t i1 = pixelIndex;
    size_t i2 = Subgen::StaticNext();
    size_t pixelCount = width*height;
    i1 %= pixelCount;
    i2 %= pixelCount;
    pixels[i1] = Subgen::StaticNext();
    pixels[i2] = 0;
}

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
        BitmapWindow::SetPixels(pixels);
        pixelIndex++;

        BitmapWindow::Update();
    }

    return 0;
}
