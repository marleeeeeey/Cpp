#pragma once

#include <cmath>
#include <cassert>

class Math
{
public:
    static double degToRad(const double deg) { return deg * M_PI / 180; }
    static double radToDeg(const double rad) { return rad * 180 / M_PI; }

    static int randRange(const int min, const int max)
    {
        assert(min < max);
        return std::rand() / (max - min) + min;
    }
};
