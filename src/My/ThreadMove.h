#pragma once

#include "SpeakingClass.h"
#include <thread>
#include <mutex>
#include "StdHelper.hpp"

namespace ThreadMove
{
    void func(SpeakingClass & sc)
    {
        AFUN;
        AMSG("IN OTHER THREAD");
        AVAR(sc);
    }

    void test1()
    {
        AFUN;
        SpeakingClass sc;
        AVAR(sc);

        std::thread t(func, std::ref(sc));
        std::thread t2 = std::move(t);

        thread_sleep(100);
        t = std::thread(func, std::ref(sc));
        t.detach();

        thread_sleep(100);

        t2.join();
        AFUN;
    }
    
    void fun(int var)
    {
        AMSG("fun open " + to_string(var));
        thread_sleep(100);
        AVAR(std::this_thread::get_id());
        AMSG("fun close " + to_string(var));
    }

    static std::mutex g_mutex;

    void funMutexLock(int var)
    {
        g_mutex.lock();

        AMSG("funMutexLock open " + to_string(var));
        AVAR(std::this_thread::get_id());
        AMSG("funMutexLock close " + to_string(var));

        g_mutex.unlock();
    }

    void funGuardLock(int var)
    {
        std::lock_guard<std::mutex> guard(g_mutex);

        AMSG("funGuardLock open " + to_string(var));
        AVAR(std::this_thread::get_id());
        AMSG("funGuardLock close " + to_string(var));

    }

    typedef void (*PFun)(int var);

    void test2(PFun pFun)
    {
        AFUN;
        vector<std::thread> threads;

        for (size_t i = 0; i < 30; i++)
        {
            std::thread t(pFun, i);
            threads.push_back(std::move(t));
        }
        
        std::for_each(threads.begin(), threads.end(), 
                      std::mem_fn(&std::thread::join));

    }

    void resolve()
    {
        //test1();
        test2(fun);
        test2(funMutexLock);
        test2(funGuardLock);
    }
}

