#pragma once

#include <d2d1.h>
#pragma comment(lib, "d2d1")

class DPIScale
{
    static float scaleX;
    static float scaleY;

public:
    static void Initialize(ID2D1Factory* pFactory)
    {
        FLOAT dpiX, dpiY;
#pragma warning(push)
#pragma warning(disable: 4996)
        pFactory->GetDesktopDpi(&dpiX, &dpiY);
#pragma warning(pop)
        scaleX = dpiX / 96.0f;
        scaleY = dpiY / 96.0f;
    }

    template <typename T>
    static D2D1_POINT_2F PixelsToDips(T x, T y)
    {
        return D2D1::Point2F(static_cast<float>(x) / scaleX, static_cast<float>(y) / scaleY);
    }
};
