#pragma once

#include "OopSocket/OopSocket.h"    // Order important! This is first include!
#include "StdPlus/StdPlus.h"
#include "ChatServer.hpp"

int main(int argc, char** argv)
{
    ChatServer cs;
    cs.setCmdArgs(argc, argv);
    cs.start();

    APAUSE_MSG("press any key for kill server");
    return 0;
}