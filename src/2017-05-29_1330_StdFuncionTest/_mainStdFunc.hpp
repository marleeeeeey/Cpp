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


using FuncPtr = double(*)(double, double);
using ClassFuncPtr = double(Math::*)(double, double);
using StdFuncPtr = std::function<double(double, double)>;

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

    using namespace std::placeholders;

    std::vector<StdFuncPtr> stdFuncs
    {
        sum,
        diff,
        std::bind(&Math::sum, &math, _1, _2),
        std::bind(&Math::diff, &math, _1, _2),
    };
    
    ARED(a);
    ARED(b);

    for (StdFuncPtr funPtr : stdFuncs)
    {
        AVAR(funPtr(a, b));
    }

    APAUSE;
}
