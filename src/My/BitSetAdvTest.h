#pragma once

#include "StdHelper.hpp"


namespace BitSetAdvTest
{
    void resolve()
    {
        AFUN;

        bitsetadv<8> b8;
        AVAR(b8);

        b8.setLeftBit(0);
        AVAR(b8);

        b8.setLeftBit(7);
        AVAR(b8);

        b8.setLeftBit(8);
        AVAR(b8);
    }
}