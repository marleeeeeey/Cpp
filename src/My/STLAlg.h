#pragma once
#include "StdHelper.hpp"
#include <numeric>

namespace STLAlg
{
    enum { arrSize = 10 };

    int * arr()
    {
        static int arr[arrSize];  

        return arr;
    }

    void print()
    {
        AFUN;

        for (int i = 0; i < arrSize; ++i)
        {
            AMSG(to_string(i) + " " + to_string(arr()[i]));
        }
    }

    void fill()
    {
        AFUN;
        std::fill(arr(), arr() + arrSize, 7);
    }

    void copy()
    {
        AFUN;        
        std::vector<float> floats;
        
        floats.resize(arrSize);
        std::copy(arr(), arr() + arrSize, floats.begin());

        AVAR(floats);
    }
    
    void vectorAssign()
    {
        AFUN;
        
        int vars[] = { 1, 2, 4, 5, 6, 7, 8, 4, 6, 3, 5, 7, 3 ,21 };

        AVAR(vars);
        AVAR(sizeof(vars));
        AVAR(SIZEOF_ARR(vars));
        
        vector<int> vecVars;
        AVAR(vecVars);
        vecVars.assign(vars, vars + SIZEOF_ARR(vars));
        AVAR(vecVars);

        auto vec2 = to_vector(vars, SIZEOF_ARR(vars));
        AVAR(vec2);

    }

    int myFunc(int initMult, int var)
    {
        return initMult * var;
    }

    void accumulate()
    {
        AFUN;
        vector<int> vars = { 1, 2, 4, 5, 6, 7, 8, 4, 6, 3, 5, 7, 3 ,21 };               
        AVAR(vars);

        int sum = std::accumulate(vars.begin(), vars.end(), 0);
        AVAR(sum);

        int mult = std::accumulate(vars.begin(), vars.end(), 1, myFunc);
        AVAR(mult);

        int labmdaMult = std::accumulate(vars.begin(), vars.end(), 1, 
            [](int initMult, int var)
            {
                return initMult * var;                
            });
        AVAR(labmdaMult);

        int manualSum = 0;
        int manualMult = 1;
        for (auto & var : vars)
        {
            manualSum += var;
            manualMult *= var;
        }

        AVAR(manualSum);
        AVAR(manualMult);
    }

    void resolve()
    {
        print();
        fill();
        print();
        copy();
        vectorAssign();
        accumulate();
    }
}

