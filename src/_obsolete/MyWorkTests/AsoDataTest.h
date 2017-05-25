#pragma once
#include "StdHelper.hpp"
#include "Aso.h"

namespace AsoDataTest
{
    void testAsoInp()
    {
        AFUN;

        AsoInp ai;

        for (int i = -1; i <= 75; ++i)
        {
            ASPLIT;
            AVAR(i);
            ai.setRL(i);
            AVAR(ai);
            ai.resetRL(i);
            AVAR(ai);
        }

        ASPLIT;
        ai.setNamedArg(AsoInp::NamedArg::e_request);
        AVAR(ai);
        AVAR(sizeof(ai.data()));

        AVAR(ai.getNamedArg(AsoInp::NamedArg::e_request));
        AVAR(ai.getNamedArg(AsoInp::NamedArg::e_RK));
    }

    void testAsoOut()
    {
        AFUN;
        
        AsoOut ao;

        for (int i = -1; i <= 75; ++i)
        {
            ASPLIT;
            AVAR(i);
            ao.setRL(i);
            AVAR(ao);
            ao.resetRL(i);
            AVAR(ao);
        }

        ASPLIT;
        ao.setNamedArg(AsoOut::NamedArg::e_silenceRadio);        
        AVAR(ao);
        ao.setNamedArg(AsoOut::NamedArg::e_PRGS);
        AVAR(ao);

        auto w1 = ao.data().w1;
        auto w2to5 = ao.data().w2to5;
        
        AVAR(sizeof(ao.data()));

        AVAR(sizeof(w1));
        AVAR(sizeof(w2to5));


        AVAR(ao.getNamedArg(AsoOut::NamedArg::e_priorityRLS));
        AVAR(ao.getNamedArg(AsoOut::NamedArg::e_silenceRadio));
        AVAR(ao.getNamedArg(AsoOut::NamedArg::e_PRGS));
    }

    void resolve()
    {
        AFUN;
        testAsoInp();
        testAsoOut();        
    }

}

