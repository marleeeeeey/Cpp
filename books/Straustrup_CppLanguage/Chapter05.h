#pragma once
#include "StdHelper.hpp"


namespace StProgLangChapter05
{
    static void resolve()
    {
        AFUN;

        struct Link
        {
            Link * l1;
            Link * l2;
        };


        struct ModernLink
        {
            //  ModernLink ml_1;    // Так делать нельзя, 
                                    // потому что нет полного
                                    // определения типа
        };

    }
}