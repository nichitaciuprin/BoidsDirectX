#pragma once

typedef uint32_t Pixel;

const Pixel BLACK = 0x00000000;
const Pixel WHITE = 0xFFFFFFFF;
const Pixel RED   = 0x00FF0000;
const Pixel GREEN = 0x0000FF00;
const Pixel BLUE  = 0x000000FF;

class Bitmap
{
public:
    vector<uint32_t> pixels;

    Bitmap()
    {
        pixels = vector<uint32_t>();
    }

    uint32_t Width() const
    {
        return width;
    }
    uint32_t Height() const
    {
        return height;
    }
    void Resize(uint32_t _width, uint32_t _height)
    {
        width = _width;
        height = _height;
        auto pixelCount = width*height;
        if (pixels.size() < pixelCount)
            pixels.resize(pixelCount);
    }
    void Clear(Pixel pixel)
    {
        fill(pixels.begin(), pixels.end(), pixel);
    }
    Pixel GetPixel(uint32_t x, uint32_t y) const
    {
        if (x > width) return 0x00000000;
        if (y > height) return 0x00000000;
        return pixels[x+y*width];
    }
    void SetPixel(uint32_t x, uint32_t y, Pixel pixel)
    {
        if (x > width) return;
        if (y > height) return;
        pixels[x+y*width] = pixel;
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

    void DrawBorder(Pixel pixel)
    {
        DrawLine(0      ,0       ,0      ,height-1,pixel);
        DrawLine(0      ,0       ,width-1,0       ,pixel);
        DrawLine(width-1,height-1,width-1,0       ,pixel);
        DrawLine(width-1,height-1,0      ,height-1,pixel);
    }
    void DrawX(Pixel pixel)
    {
        DrawLine(0,0,width-1,height-1,pixel);
        DrawLine(width-1,0,0,height-1,pixel);
    }
    void DrawSquare(Pixel pixel)
    {
        for (uint32_t x = 0; x < 20; x++)
        for (uint32_t y = 0; y < 20; y++)
            SetPixel(x,y,pixel);
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

private:
    uint32_t width = 0;
    uint32_t height = 0;
};
