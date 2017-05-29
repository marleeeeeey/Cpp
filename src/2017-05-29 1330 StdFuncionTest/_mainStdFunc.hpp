#include "StdPlus/StdPlus.h"


typedef double(*FuncPtr)(double, double);


double sum(double a, double b)
{
    return a + b;
}

double diff(double a, double b)
{
    return a - b;
}

int main(int argc, char ** argv)
{
    std::vector<FuncPtr> funcs
    {
        sum,
        diff,
    };

    double a = 2;
    double b = 5;
    ARED(a);
    ARED(b);


    for (FuncPtr funPtr : funcs)
    {
        AVAR(funPtr(a, b));
    }

    APAUSE;
}