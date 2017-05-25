#pragma once

//#include "SpeakingClass.h"
typedef int SpeakingClass;
typedef SpeakingClass * PSC;

#include "StdHelper.hpp"


namespace RefToPointer
{
    void fun1(SpeakingClass * pSc)
    {
        AFUN;
        AVAR(pSc);
        AVAR(*pSc);
    }

    void fun2(SpeakingClass & sc)
    {
        AFUN;
        AVAR(&sc);
        AVAR(sc);
    }

    void fun3(SpeakingClass * & sc)
    {
        AFUN;
        AVAR(sc);    // выводит указатель
        sc = nullptr;
        AVAR(sc);
    }

    void resolve()
    {
        AFUN;

//         SpeakingClass * pSc = new SpeakingClass(1);
//         SpeakingClass & sc = *pSc;
//         AVAR(sc);
//         AVAR(&sc);
//         fun1(&sc);
//         fun2(sc);
//         fun3(pSc);
// 
//         AFUN;
//         AVAR(sc);
//         AVAR(&sc);
// 
//         fun3(pSc);
//         AFUN;
//         AVAR(sc);   
//         AVAR(&sc);
//         AVAR(pSc);

        PSC pSc = new SpeakingClass;
        AVAR(pSc);
        fun3(pSc);
        AVAR(pSc);
        delete pSc;
    }
}

