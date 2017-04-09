#pragma once

#include "StdHelper.hpp"
#include "../TestShared.h"


namespace ProgrammLangParser
{
    const string fileName = "testFile.txt";

    void resolve()
    {
        AFUN;

        string str = readFileToString(fileName);
        AVAR(str);

        

    }
}