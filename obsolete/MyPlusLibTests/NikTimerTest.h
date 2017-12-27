#pragma once

#include "mm_timer.h"
#include <thread>


namespace NikTimerTest
{
    class Tester
    {
    public:
        Tester()
        {
            static int counter = 0;
            counter++;
            m_id = counter;
        }

        void timeFunc()
        {
            AFUN;
            AVAR(m_id);
        }

    private:
        friend std::ostream & operator<<(std::ostream & os, const Tester & d);
        int m_id = 0;
    };

    std::ostream & operator<<(std::ostream & os, const Tester & d)
    {
        os << d.m_id;
        return os;
    }

    void time1000()
    {
        AFUN;
    }

    void time1000_2()
    {
        AFUN;
    }

    void resolve()
    {
        AFUN;
        mm_timer timer1(1000, time1000);
        thread_sleep(500);

        mm_timer timer2(500, time1000_2);

        mm_timer timer3(400, []()
                             {
                                 AFUN;
                             }
        );

        Tester t;

        // запуск таймера на функции класса
        mm_timer timer4(800,  &Tester::timeFunc,  &t);

        thread_sleep(5000);
    }
}