#pragma once

struct Bitmap
{
    uint32_t* pixels;
    uint16_t width;
    uint16_t height;
};

void DrawSquare(uint32_t* pixels, size_t width)
{
    for (size_t row    = 0; row    < 20; row++)
    for (size_t column = 0; column < 20; column++)
    {
        pixels[column+row*width] = ~(uint32_t)0;
    }
}
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
void Line(uint32_t* pixels, size_t width, int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (true)
    {
        // setPixel(x0,y0);
        if (x0 == x1 && y0 == y1) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 <  dy) { err += dx; y0 += sy; }
    }
}