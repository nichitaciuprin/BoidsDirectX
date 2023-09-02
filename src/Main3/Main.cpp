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
typedef int (__cdecl *MYPROC)(LPCWSTR);

// int main( void )
// {
//     HINSTANCE hinstLib;
//     MYPROC ProcAdd;
//     BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

//     // Get a handle to the DLL module.

//     hinstLib = LoadLibrary(TEXT("MyPuts.dll"));

//     // If the handle is valid, try to get the function address.

//     if (hinstLib != NULL)
//     {
//         ProcAdd = (MYPROC) GetProcAddress(hinstLib, "myPuts");

//         // If the function address is valid, call the function.

//         if (NULL != ProcAdd)
//         {
//             fRunTimeLinkSuccess = TRUE;
//             (ProcAdd) (L"Message sent to the DLL function\n");
//         }
//         // Free the DLL module.

//         fFreeResult = FreeLibrary(hinstLib);
//     }

//     // If unable to call the DLL function, use an alternative.
//     if (! fRunTimeLinkSuccess)
//         printf("Message printed from executable\n");

//     return 0;

// }
void DrawSquare(uint32_t* pixels, size_t width)
{
    for (size_t row    = 0; row    < 20; row++)
    for (size_t column = 0; column < 20; column++)
    {
        pixels[column+row*width] = ~(uint32_t)0;
    }
}
// void Line(uint32_t* pixels, size_t width, int x0, int y0, int x1, int y1)
// {
//     int dx = abs(x1 - x0);
//     int dy = abs(y1 - y0);
//     int sx = x0 < x1 ? 1 : -1;
//     int sy = y0 < y1 ? 1 : -1;
//     int err = (dx > dy ? dx : -dy) / 2;
//     int e2;

//     while (true)
//     {
//         // setPixel(x0,y0);
//         if (x0 == x1 && y0 == y1) break;
//         e2 = err;
//         if (e2 > -dx) { err -= dy; x0 += sx; }
//         if (e2 <  dy) { err += dx; y0 += sy; }
//     }
// }
// void Duno(uint32_t* pixels, size_t width, size_t x1, size_t y1, size_t x2, size_t y2)
// {
//     auto dx = x2 - x1;
//     auto dy = y2 - y1;
//     for (size_t i = 0; i < dx; i++)
//     {
//         auto y = y1 + dy * ((x1+i) - x1) / dx;
//         plot(x, y);
//     }
// }

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
