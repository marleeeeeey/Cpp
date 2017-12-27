#pragma once

#include "StdHelper.hpp"
#include "SpeakingClass.h"
#include <thread>

namespace ThreadRef
{
    class SpeakingThread : public SpeakingClass
    {
    public:
        using SpeakingClass::SpeakingClass;

        void testRunThisInOtherThread()
        {
            std::thread t(&ThreadRef::SpeakingThread::func, this);
            t.detach();
        }

    private:
        void func()
        {
            AFUN;
            AVAR(std::this_thread::get_id());
        }
    };

    void resolve()
    {
        AFUN;
        AVAR(std::this_thread::get_id());
        SpeakingThread st;

        SpeakingThread st2(st);

        st.testRunThisInOtherThread();
    }
}