#pragma once
#include "SpeakingClass.h"

namespace StaticPrint
{
#define TTT(var) AVAR(#var)

    void resolve()
    {
        AFUN;

//         {
//             static bool isFirstRun = true;
//             if (isFirstRun)
//             {
//                 isFirstRun = false;
// 
//             }
//         }

        TTT(SpeakingClass sk);

        //SpeakingClass sk2;

    }
}

