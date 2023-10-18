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

    Bitmap(int widthNew, int heightNew)
    {
        pixels = vector<uint32_t>();
        Resize(widthNew, heightNew);
    }

    void Resize(int widthNew, int heightNew)
    {
        if (widthNew < 1) throw exception("Bitmap widthNew < 1");
        if (heightNew < 1) throw exception("Bitmap heightNew < 1");
        width = widthNew;
        height = heightNew;
        auto pixelCount = width * height;
        if (pixels.size() < pixelCount)
            pixels.resize(pixelCount);
    }
    int Width() const
    {
        return width;
    }
    int Height() const
    {
        return height;
    }

    void Fill(Pixel pixel)
    {
        fill(pixels.begin(), pixels.end(), pixel);
    }
    void SetPixel(int x, int y, Pixel pixel)
    {
        // TODO remove guard
        // if (x > width - 1) return;
        // if (y > height - 1) return;

        auto i = x + y * width;
        pixels[i] = pixel;
    }

    void DrawTriangle(Vector3 p0, Vector3 p1, Vector3 p2, Pixel pixel)
    {
        Vector3 v1, v2 = p1;
        Vector3 v3, v4 = p2;
        Vector3 v0, v5 = p0;
        bool include1, include2, include3;
        ClipLineByZ3(v0, v1, include1);
        ClipLineByZ3(v2, v3, include2);
        ClipLineByZ3(v4, v5, include3);
        auto includeCount = include1 + include2 + include3;
        if (includeCount == 0) return;
        if (includeCount == 3)
        {
            if (p0.z != 0) p0 /= p0.z;
            if (p1.z != 0) p1 /= p1.z;
            if (p2.z != 0) p2 /= p2.z;
            DrawTriangleProjected(p0, p1, p2, pixel);
            return;
        }
        if (include1) { if (v0.z != 0) v0 /= v0.z; if (v1.z != 0) v0 /= v1.z; }
        if (include2) { if (v2.z != 0) v0 /= v2.z; if (v3.z != 0) v0 /= v3.z; }
        if (include3) { if (v4.z != 0) v0 /= v4.z; if (v5.z != 0) v0 /= v5.z; }
    }
    void DrawTriangleProjected(Vector3 p0, Vector3 p1, Vector3 p2, Pixel pixel)
    {
        if (!Vector3TriangleIsClockwise(p0, p1, p2)) return;
        DrawLineProjected(p0, p1, pixel);
        DrawLineProjected(p1, p2, pixel);
        DrawLineProjected(p2, p0, pixel);
    }
    void DrawShape3(Vector3 p0, Vector3 p1, Vector3 p2, Pixel pixel)
    {
        if (!Vector3TriangleIsClockwise(p0, p1, p2)) return;
        DrawLineProjected(p0, p1, pixel);
        DrawLineProjected(p1, p2, pixel);
        DrawLineProjected(p2, p0, pixel);
    }
    void DrawShape4(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, Pixel pixel)
    {
        if (!Vector3TriangleIsClockwise(p0, p1, p2)) return;
        DrawLineProjected(p0, p1, pixel);
        DrawLineProjected(p1, p2, pixel);
        DrawLineProjected(p2, p3, pixel);
        DrawLineProjected(p3, p0, pixel);
    }
    void DrawLine(Vector3 v0, Vector3 v1, Pixel pixel)
    {
        float nearZ = 0.1f;
        v0.z -= nearZ;
        v1.z -= nearZ;
        if (!ClipLineByZ(v0, v1)) return;
        v0.z += nearZ;
        v1.z += nearZ;
        if (v0.z != 0) v0 /= v0.z;
        if (v1.z != 0) v1 /= v1.z;
        DrawLineProjected(v0, v1, pixel);
    }
    void DrawLineProjected(Vector3 v0, Vector3 v1, Pixel pixel)
    {
        if (!ClipLine(v0.x, v0.y, v1.x, v1.y)) return;
        int outX0, outY0;
        int outX1, outY1;
        ToScreenSpace(v0, &outX0, &outY0);
        ToScreenSpace(v1, &outX1, &outY1);
        DrawLine(outX0, outY0, outX1, outY1, pixel);
    }
    void DrawLine(int x0, int y0, int x1, int y1, Pixel pixel)
    {
        int dx = abs(x1 - x0);
        int dy = abs(y1 - y0);
        int sx = x0 < x1 ? 1 : -1;
        int sy = y0 < y1 ? 1 : -1;

        if (dx > dy)
        {
            int err = dx / 2;
            for (int i = 0; i < dx; i++)
            {
                SetPixel(x0, y0, pixel);
                if (err < dy) { err += dx; y0 += sy; }
                              { err -= dy; x0 += sx; }
            }
        }
        else if (dx < dy)
        {
            int err = dy / 2;
            for (int i = 0; i < dy; i++)
            {
                SetPixel(x0, y0, pixel);
                if (err < dx) { err += dy; x0 += sx; }
                              { err -= dx; y0 += sy; }
            }
        }
        else
        {
            for (int i = 0; i < dx; i++)
            {
                SetPixel(x0, y0, pixel);
                x0 += sx;
                y0 += sy;
            }
        }
    }

    void DrawCube(Matrix modelView)
    {
        float h = 0.5f;
        Vector3 vertices[] =
        {
            Vector3{-h,-h,-h},
            Vector3{-h,-h, h},
            Vector3{-h, h,-h},
            Vector3{-h, h, h},
            Vector3{ h,-h,-h},
            Vector3{ h,-h, h},
            Vector3{ h, h,-h},
            Vector3{ h, h, h}
        };

        int indices[12][2] =
        {
            0,1,
            1,5,
            5,4,
            4,0,
            2,3,
            3,7,
            7,6,
            6,2,
            0,2,
            1,3,
            5,7,
            4,6
        };

        for (size_t i = 0; i < 8; i++)
            vertices[i] *= modelView;

        for (size_t i = 0; i < 12; i++)
        {
            auto i0 = indices[i][0];
            auto i1 = indices[i][1];
            DrawLine(vertices[i0], vertices[i1], RED);
        }
    }
    void DrawCube2(Matrix modelView)
    {
        float h = 0.5f;

        Vector3 vertexData[] =
        {
            Vector3{-h,-h,-h},
            Vector3{-h,-h, h},
            Vector3{-h, h,-h},
            Vector3{-h, h, h},
            Vector3{ h,-h,-h},
            Vector3{ h,-h, h},
            Vector3{ h, h,-h},
            Vector3{ h, h, h}
        };

        int indexData[12][3] =
        {
            0, 2, 6,
            6, 4, 0,
            4, 6, 7,
            7, 5, 4,
            5, 7, 3,
            3, 1, 5,
            1, 3, 2,
            2, 0, 1,
            2, 3, 7,
            7, 6, 2,
            1, 0, 4,
            4, 5, 1,
        };

        for (int i = 0; i < 8; i++)
            vertexData[i] *= modelView;

        // for (int i = 0; i < 12; i++)
        // {
        //     auto i0 = indexData[i][0];
        //     auto i1 = indexData[i][1];
        //     auto i2 = indexData[i][2];
        //     DrawTriangle(vertexData[i0], vertexData[i1], vertexData[i2]);
        // }

        for (int i = 1; i < 12; i++)
        {
            auto i0 = indexData[i][0];
            auto i1 = indexData[i][1];
            auto i2 = indexData[i][2];
            DrawTriangle(vertexData[i0], vertexData[i1], vertexData[i2], BLUE);
        }

        {
            auto i0 = indexData[0][0];
            auto i1 = indexData[0][1];
            auto i2 = indexData[0][2];
            DrawTriangle(vertexData[i0], vertexData[i1], vertexData[i2], RED);
        }
    }
    void ToScreenSpace(Vector3 point, int* outX, int* outY)
    {
        point.y = -point.y;
        point.x += 1.0f;
        point.y += 1.0f;
        point.x /= 2;
        point.y /= 2;
        *outX = (int)((width - 1) * point.x);
        *outY = (int)((height - 1) * point.y);
    }

    void DrawBorder(Pixel pixel)
    {
        int x = width - 1;
        int y = height - 1;
        DrawLine(0, 0, 0, y, pixel);
        DrawLine(0, 0, x, 0, pixel);
        DrawLine(x, y, x, 0, pixel);
        DrawLine(x, y, 0, y, pixel);
    }
    void DrawX(Pixel pixel)
    {
        int x = width - 1;
        int y = height - 1;
        DrawLine(0, 0, x, y, pixel);
        DrawLine(x, 0, 0, y, pixel);
    }
    void DrawCross(Pixel pixel)
    {
        int centerX = width / 2;
        int centerY = height / 2;
        int x = width - 1;
        int y = height - 1;
        DrawLine(centerX, 0, centerX, y, pixel);
        DrawLine(0, centerY, x, centerY, pixel);
    }
    void DrawSquare(Pixel pixel)
    {
        int size = 20;
        for (int x = 0; x < MathClamp(size, 0, width - 1); x++)
        for (int y = 0; y < MathClamp(size, 0, height - 1); y++)
            SetPixel(x,y,pixel);
    }
    void ScanEffectRandom(size_t iteration)
    {
        size_t i1 = iteration;
        size_t i2 = Subgen::StaticNext();
        size_t pixelCount = width * height;
        i1 %= pixelCount;
        i2 %= pixelCount;
        pixels[i1] = Subgen::StaticNext();
        pixels[i2] = 0;
    }

    void DrawLineShort(int x0, int y0, int x1, int y1, Pixel pixel)
    {
        int dx = abs(x1 - x0);
        int dy = abs(y1 - y0);
        int sx = x0 < x1 ? 1 : -1;
        int sy = y0 < y1 ? 1 : -1;

        int err = (dx > dy ? dx : -dy) / 2;
        int err2;

        while (true)
        {
            SetPixel(x0, y0, pixel);
            if (x0 == x1 && y0 == y1) break;
            err2 = err;
            if (err2 > -dx) { err -= dy; x0 += sx; }
            if (err2 <  dy) { err += dx; y0 += sy; }
        }
    }

private:
    int width = 0;
    int height = 0;
};
