#pragma once

#include "Earth.hpp"

namespace TestGeoCoord
{
    void firstTest()
    {
        AFUN;

        EarthPoint p1{ deg2rad(55.696727), deg2rad(37.896046) };
        EarthPoint p2{ deg2rad(55.726996), deg2rad(37.918706) };

        AVAR(p1);
        AVAR(p2);

        EarthDirection ed = getEarthDirection(p1, p2);
        AVAR(ed);

        EarthPoint p2_2 = getEarthPoint(p1, ed);
        AVAR(p2_2);

        EarthPoint p2_3 = p1 + ed;
        AVAR(p2_3);
    }

	void resolve()
	{
        AFUN;

        firstTest();
        ASPLIT;
	}
}