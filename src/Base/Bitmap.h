#pragma once

typedef uint32_t Pixel;

class Bitmap
{
public:
    vector<uint32_t> pixels;
    const Pixel BLACK = 0;
    const Pixel WHITE = ~BLACK;

    Bitmap(uint32_t _width, uint32_t _height)
    {
        width = _width;
        height = _height;
        pixels = vector<uint32_t>();
        pixels.resize(width*height);
    }
    void Clear(Pixel pixel)
    {
        fill(pixels.begin(), pixels.end(), pixel);
    }
    void SetPixel(uint32_t x, uint32_t y, Pixel pixel)
    {
        if (x > width) return;
        if (y > height) return;
        pixels[x+y*width] = pixel;
    }
    void DrawSquare()
    {
        for (int x = 0; x < 20; x++)
        for (int y = 0; y < 20; y++)
            SetPixel(x,y,WHITE);
    }
    void ScanEffectRandom(size_t iteration)
    {
        size_t i1 = iteration;
        size_t i2 = Subgen::StaticNext();
        size_t pixelCount = width*height;
        i1 %= pixelCount;
        i2 %= pixelCount;
        pixels[i1] = Subgen::StaticNext();
        pixels[i2] = 0;
    }
    void DrawLine(int x0, int y0, int x1, int y1, Pixel pixel)
    {
        int dx = abs(x1 - x0);
        int dy = abs(y1 - y0);
        int sx = x0 < x1 ? 1 : -1;
        int sy = y0 < y1 ? 1 : -1;
        int err = (dx > dy ? dx : -dy) / 2;
        int e2;

        while (true)
        {
            SetPixel(x0,y0,pixel);
            if (x0 == x1 && y0 == y1) break;
            e2 = err;
            if (e2 > -dx) { err -= dy; x0 += sx; }
            if (e2 <  dy) { err += dx; y0 += sy; }
        }
    }

private:
    uint32_t width = 0;
    uint32_t height = 0;
};
