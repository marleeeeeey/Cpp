#pragma once

#include "StdHelper.hpp"
#include "Chapter06_OriginalCalc.h"
#include "Chapter06_ModifyCalc.h"

namespace StProgLangChapter06
{
    static void resolve(int argc = 0, char** argv = nullptr)
    {
        AFUN;
        //StProgLangChapter06_OriginalCalc::resolve(argc, argv);
        StProgLangChapter06_ModifyCalc::resolve(argc, argv);

    }

}