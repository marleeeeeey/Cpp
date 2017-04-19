#pragma once

#include "StdHelper.hpp"

namespace DebugOut
{
    void resolve()
    {
        AFUN;

        enum { e_size = 10, };
        int numbers[e_size];
        AVAR(numbers);
        AVAR(PrintArr<int>(numbers, e_size));

        bool isTrue = true;
        bool isFalse = false;

        AVAR(isTrue);
        AVAR(isFalse);

        AVAR(to_string(isTrue));
        AVAR(to_string(isFalse));

        double isDouble = 435.453;
        AVAR(isDouble);
        AVAR(to_string(isDouble));

        AVAR(isTrue);
    }
}

