#pragma once

#include "OopSocket/OopSocket.h"
#include "StdPlus/StdPlus.h"
#include "ChatServer.hpp"

int main(int argc, char** argv)
{
    AFUN;

    ChatServer cs;
    cs.setCmdArgs(argc, argv);
    cs.start();

    APAUSE_MSG("kill me!");

    return 0;
}