#pragma once


namespace StrangeTest
{
    void resolve()
    {
        AFUN;

        long long ll = 190;

        long long * pll = &ll;

        AVAR(pll);
        AVAR(*pll);

        char * ch = (char *)pll;

        AHEX(ch);
        AVAR(*ch);
    }
}


