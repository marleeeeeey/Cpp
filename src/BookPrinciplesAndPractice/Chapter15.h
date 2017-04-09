#include <math.h>
#include "StdHelper.hpp"

namespace StPrinciplesChapter15
{
    int fac(int n)
    {
        int r = 1;
        while (n > 1)
        {
            r *= n;
            --n;
        }
        return r;
    }

    double term(double x, int n)
    {
        return pow(x, n) / fac(n);
    }

    double expe(double x, int n)
    {
        double sum = 0;
        for (int i = 0; i < n; ++i) 
            sum += term(x, i);

        return sum;
    }



    void resolve()
    {
        AFUN;

    }
}