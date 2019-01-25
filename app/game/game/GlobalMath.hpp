#pragma once

#include <cmath>
#include <cassert>

class Math
{
public:
    inline static double degToRad(double deg) { return deg * M_PI / 180; }
    inline static double radToDeg(double rad) { return rad * 180 / M_PI; }
    inline static int randRange(int min, int max)
    {
        assert(min < max);
        return std::rand() / (max - min) + min;
    }
};
