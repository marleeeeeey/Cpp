#pragma once
#include "StdHelper.hpp"



namespace DataDaceThread
{
    struct Counter 
    {
        int value;

        Counter() : value(0){}

        void increment(){
            ++value;
        }
    };

    int resolve() 
    {
        AFUN;

        Counter counter;

        std::vector<std::thread> threads;
        for (int i = 0; i < 10; ++i)
        {
            threads.push_back(std::thread([&counter]()
            {
                for (int i = 0; i < 1000; ++i)
                {
                    counter.increment();
                }
            }));
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        AVAR(counter.value);

        return 0;
    }
}