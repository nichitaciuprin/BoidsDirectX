#include "../Base/Base.h"
#include "TestWindow.h"

#if RAND_MAX == 32767
#define Rand32() ((rand() << 16) + (rand() << 1) + (rand() & 1))
#else
#define Rand32() rand()
#endif

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
    TestWindow_Create();

    while (TestWindow_Exists())
    {
        ChangePixelsRandomly(TestWindow_pixels, TestWindow_width, TestWindow_height);
        TestWindow_Update();
    }

    return 0;
}
