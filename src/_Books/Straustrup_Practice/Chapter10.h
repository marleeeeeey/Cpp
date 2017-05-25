#pragma  once
#include "StdHelper.hpp"
#include "..\TestShared.h"

namespace StPrinciplesChapter10
{
    struct Point
    {
        int x;
        int y;
    };

    std::ostream & operator<<(std::ostream & os, const Point & p)
    {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }

    std::istream & operator>>(std::istream & is, Point & p)
    {
        int x;
        int y;
        char ch1;
        char ch2;
        char ch3;

        enum 
        {
            e_ch1 = '(',
            e_ch2 = ',',
            e_ch3 = ')',
        };

        is >> ch1 >> x >> ch2 >> y >> ch3;
        
        if (!is)
            return is;

        if (ch1 != e_ch1 || ch2 != e_ch2 || ch3 != e_ch3)
            throwError("Format read");

        p = Point{ x, y };
        return is;
    }

    typedef vector<Point> Points;

    Points & originalPoints()
    {
        static Points points;
        return points;
    }

    void readOriginalPoints()
    {
        for (Point p; inputFile() >> p;)
            originalPoints().push_back(p);

        inputFile().clear();
    }

    void saveOriginalPoints()
    {
        for (auto & p : originalPoints())
        {
            outputFile() << p << std::endl;
        }
    }

    void printOriginalPoints()
    {
        for (auto & p : originalPoints())
        {
            AVAR(p);
        }
    }

    void resolve()
    {
        AFUN;
        readOriginalPoints();
        printOriginalPoints();
        saveOriginalPoints();
        inputFile().close();
        outputFile().close();
    }
}
