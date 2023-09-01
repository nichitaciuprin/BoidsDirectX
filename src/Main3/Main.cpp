#include "../Base/Base.h"
#include "BitmapWindow.h"

int pixelIndex = 0;
void ChangePixelsRandomly(uint32_t* pixels, int width, int height)
{
    int i1 = pixelIndex;
    int i2 = Rand32();
    int pixelCount = width*height;
    i1 = i1 % pixelCount;
    i2 = i2 % pixelCount;
    pixels[i1] = Rand32();
    pixels[i2] = 0;
    pixelIndex++;
}

int main()
{
    BitmapWindow::Create();

    while (BitmapWindow::Exists())
    {
        CheckFPS();

        uint32_t* pixels;
        int width;
        int height;
        BitmapWindow::GetBitmapInfo(&pixels, &width, &height);

        ChangePixelsRandomly(pixels, width, height);

        BitmapWindow::Update();
    }

    return 0;
}
