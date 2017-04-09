#pragma once

#include "StdHelper.hpp"

namespace RandomTest
{
    void resolve()
    {
        for (int i = 0; i < 20; i++)
        {
            //AVAR(getRandom<int>(1, 99));

//             AVAR(isProbability(50));
// 
//             AVAR(getRandom(5., 10.));

            AVAR(getRandomVector<int>(0, 10, 5));
        }
    }
}

