#pragma once

typedef uint32_t Pixel;

const Pixel BLACK = 0x00000000;
const Pixel WHITE = 0xFFFFFFFF;
const Pixel RED   = 0x00FF0000;
const Pixel GREEN = 0x0000FF00;
const Pixel BLUE  = 0x000000FF;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

const int xmin = -1;
const int xmax =  1;
const int ymin = -1;
const int ymax =  1;

int ComputeOutCode(float x, float y)
{
	int code = INSIDE;
	if      (x < xmin) code |= LEFT;
	else if (x > xmax) code |= RIGHT;
	if      (y < ymin) code |= BOTTOM;
	else if (y > ymax) code |= TOP;
	return code;
}

// ignore uninitialized float x, y;
#pragma warning(push)
#pragma warning(disable:6001)
#pragma warning(disable:4701)
bool ClipLine(float& x0, float& y0, float& x1, float& y1)
{
	int code0 = ComputeOutCode(x0, y0);
	int code1 = ComputeOutCode(x1, y1);

	while (true)
    {
		if (!(code0 | code1)) return true;  // points inside
        if (  code0 & code1 ) return false; // points in same outside zone

        int code =
            code1 > code0 ?
            code1 : code0;

        float x, y;

        if (code & TOP)    { x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0); y = ymax; } // point is above the clip window
        if (code & BOTTOM) { x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0); y = ymin; } // point is below the clip window
        if (code & RIGHT)  { y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0); x = xmax; } // point is to the right of clip window
        if (code & LEFT)   { y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0); x = xmin; } // point is to the left of clip window

        if (code == code0) { x0 = x; y0 = y; code0 = ComputeOutCode(x0, y0); }
        else               { x1 = x; y1 = y; code1 = ComputeOutCode(x1, y1); }
	}

	return true;
}
#pragma warning(pop)

bool InFrustum(Vector3 point)
{
    if (point.z / MathAbs(point.x) < 1) return false;
    if (point.z / MathAbs(point.y) < 1) return false;
    return true;
}

class Bitmap
{
public:
    vector<uint32_t> pixels;

    Bitmap()
    {
        pixels = vector<uint32_t>();
    }

    void DrawCube(Vector3 position, Vector3 direction)
    {
        Vector3 vertices[] =
        {
            Vector3{-0.5f,-0.5f,-0.5f},
            Vector3{-0.5f,-0.5f, 0.5f},
            Vector3{-0.5f, 0.5f,-0.5f},
            Vector3{-0.5f, 0.5f, 0.5f},
            Vector3{ 0.5f,-0.5f,-0.5f},
            Vector3{ 0.5f,-0.5f, 0.5f},
            Vector3{ 0.5f, 0.5f,-0.5f},
            Vector3{ 0.5f, 0.5f, 0.5f}
        };

        for (auto& v : vertices)
            v *= 2;

        uint16_t indices[12][2] =
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

        auto world = MatrixWorld(position,direction);
        for (size_t i = 0; i < 8; i++)
        {
            vertices[i] = vertices[i] * world;
        }

        for (auto& v : vertices)
            v /= v.z;

        for (size_t i = 0; i < 12; i++)
        {
            auto i0 = indices[i][0];
            auto i1 = indices[i][1];
            DrawLine(vertices[i0],vertices[i1]);
        }
    }
    void DrawLine(Vector3 v0, Vector3 v1)
    {
        if (v0.z < 0 && v1.z < 0) return;

        ClipLine(v0,v1);

        // if (v0.z < 0)
        // {
        //     v0 += (v0-v1)/(v1.z-v0.z)*v0.z;
        // }
        // else if (v1.z < 0)
        // {
        //     v1 += (v1-v0)/(v0.z-v1.z)*v1.z;
        // }

        uint32_t outX0, outY0;
        uint32_t outX1, outY1;
        ToScreenSpace(v0,&outX0,&outY0);
        ToScreenSpace(v1,&outX1,&outY1);
        DrawLine(outX0,outY0,outX1,outY1,RED);
    }
    void ToScreenSpace(Vector3 point, uint32_t* outX, uint32_t* outY)
    {
        auto scale = 100;
        *outX = (width  / 2) + (uint32_t)(point.x * scale);
        *outY = (height / 2) - (uint32_t)(point.y * scale);
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
        // TODO check should be removed
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
    void DrawCross(Pixel pixel)
    {
        DrawLine(width/2,0,width/2,height-1,pixel);
        DrawLine(0,height/2,width-1,height/2,pixel);
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
