#include "../Base/Base.h"

void ChangePixelsRandomly(uint32_t* pixels, size_t width, size_t height, size_t pixelIndex)
{
    size_t i1 = pixelIndex;
    size_t i2 = Rand32();
    size_t pixelCount = width*height;
    i1 = i1 % pixelCount;
    i2 = i2 % pixelCount;
    pixels[i1] = Rand32();
    pixels[i2] = 0;
}

int main()
{
    BitmapWindow::Create();

    size_t pixelIndex = 0;

    while (BitmapWindow::Exists())
    {
        CheckFPS();

        uint32_t* pixels;
        size_t width;
        size_t height;
        BitmapWindow::GetBitmapInfo(&pixels, &width, &height);

        ChangePixelsRandomly(pixels, width, height, pixelIndex);
        pixelIndex++;

        BitmapWindow::Update();
    }

    return 0;
}
