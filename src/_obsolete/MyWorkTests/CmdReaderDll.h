#pragma once
#include "StdHelper.hpp"
#include "CmdReader.h"

namespace CmdReaderDll
{
    void resolve(int argc, char* argv[])
    {
        AFUN;

        oneCmdReader().setParams(argc, argv);

        bool isTest = false;

        oneCmdReader().addCommand(BoolCmdMaster("test", isTest));

        oneCmdReader().parseParams();

        AVAR(isTest);
    }
}

