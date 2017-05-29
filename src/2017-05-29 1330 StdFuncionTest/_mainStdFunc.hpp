#include "StdPlus/StdPlus.h"

double sum(double a, double b)
{
    return a + b;
}

double diff(double a, double b)
{
    return a - b;
}

class Math
{
public:

    double sum(double a, double b)
    {
        return a + b;
    }

    double diff(double a, double b)
    {
        return a - b;
    }

};


typedef double(*FuncPtr)(double, double);
typedef double(Math::*ClassFuncPtr)(double, double);
typedef std::function<double(double, double)> StdFuncPtr;

int main(int argc, char ** argv)
{
    Math math;

    double a = 2;
    double b = 5;
    ARED(a);
    ARED(b);

    // *** use global func ptr ***

    std::vector<FuncPtr> funcs
    {
        sum,
        diff,
    };

    for (FuncPtr funPtr : funcs)
    {
        AVAR(funPtr(a, b));
    }


    // *** use member class func ptr ***

    std::vector<ClassFuncPtr> classFuncs
    {
        &Math::sum,
        &Math::diff,

    };


    for (ClassFuncPtr classFunPtr : classFuncs)
    {
        AVAR((math.*classFunPtr)(a, b));
    }


    // *** use std::function for both ***

    std::vector<StdFuncPtr> stdFuncs
    {
        sum,
        diff,
        std::bind(&Math::sum, &math, a, b),
        std::bind(&Math::diff, &math, a, b),
    };

    for (StdFuncPtr funPtr : stdFuncs)
    {
        AVAR(funPtr(a, b));
    }

    APAUSE;
}
