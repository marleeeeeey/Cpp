#pragma once
#include "StdHelper.hpp"

namespace UseLambda
{
    bool f2(int x)
    {
        return x % 2 == 0;
    }

    bool f3(int x) 
    {
        return x % 3 == 0;
    }

    class f_mod
    {
    public:
        f_mod(int d) 
            : dv(d) 
        {}

        bool operator() (int x) 
        {
            return x % dv == 0;
        }

    private:
        int dv;
    };

    void resolve()
    {
        AFUN;

        std::vector<int> numbers(10);
        std::generate(numbers.begin(), numbers.end(), std::rand);
        AVAR(numbers);

        int count2 = std::count_if(numbers.begin(), numbers.end(), f2);
        AVAR(count2);

        int count3 = std::count_if(numbers.begin(), numbers.end(), f3);
        AVAR(count3);

        int count_fmod2 = std::count_if(numbers.begin(), numbers.end(), f_mod(2));
        AVAR(count_fmod2);

        int count_fmod3 = std::count_if(numbers.begin(), numbers.end(), f_mod(3));
        AVAR(count_fmod3);

        int count_lambda2 = std::count_if(numbers.begin(), numbers.end(), [](int x)
        {
            return x % 2 == 0;
        });
        AVAR(count_lambda2);

        int count_lambda3 = std::count_if(numbers.begin(), numbers.end(), [](int x)
        {
            return x % 3 == 0;
        });
        AVAR(count_lambda3);

        int count_lambda2_bool = std::count_if(numbers.begin(), numbers.end(), [](int x)->bool
        {
            return x % 2 == 0;
        });
        AVAR(count_lambda2_bool);

        int count_lambda3_bool = std::count_if(numbers.begin(), numbers.end(), [](int x)->bool
        {
            return x % 3 == 0;
        });
        AVAR(count_lambda3_bool);

        // можно предусмотреть имя для анонимной 
        // лямбда - функции и затем воспользоваться этим именем
        auto fLambda3 = [](int x)->bool
        {
            return x % 3 == 0;
        };

        int count_fLambda3 = std::count_if(numbers.begin(), numbers.end(), fLambda3);
        AVAR(count_fLambda3);        

        auto ttt = []()->int { return 1; }();
        AVAR(ttt);
    }
}

