#pragma once
#include "StdHelper.hpp"

namespace SOAnswer03
{
    class Beerus;
    class GokuBlack;

    class Goku
    {
    public:
        Goku();
        ~Goku();

        string get_Name(void);
        int get_power(void);

        
        GokuBlack* rose;
        Beerus* god;
    };

    class vegeta : public Goku
    {
    public:
        vegeta(); //an intitializtion constructor
        ~vegeta();
        string get_Name(void);
        int get_power(void);
    };

    class Beerus : public Goku
    {
    public:
        Beerus(); //an intitializtion constructor
        ~Beerus();

        string get_Name(void);
        int get_power(void);
    };

    void resolve()
    {
        AFUN;
    }
}