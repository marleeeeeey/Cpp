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


//typedef double(*FuncPtr)(double, double);
typedef std::function<double(double, double)> FuncPtr;

//typedef double(Math::*ClassFuncPtr)(double, double);
typedef std::function<double(double, double)> ClassFuncPtr;

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

    Math math;

    std::vector<ClassFuncPtr> classFuncs
    {
//         &Math::sum,
//         &Math::diff,

        std::bind(&Math::sum, &math, a, b),
        std::bind(&Math::diff, &math, a, b),
    };


    for (ClassFuncPtr classFunPtr : classFuncs)
    {
        //AVAR((math.*classFunPtr)(a, b));
        AVAR(classFunPtr(a, b));
    }

    APAUSE;
}