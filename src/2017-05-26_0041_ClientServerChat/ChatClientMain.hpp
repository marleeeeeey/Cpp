#pragma once

#include "OopSocket/OopSocket.h"    // Order important! This is first include!
#include "StdPlus/StdPlus.h"
#include "ChatClient.hpp"

int main(int argc, char** argv)
{
    APAUSE_MSG("press any key for start client");

    ChatClient client;
    client.setCmdArgs(argc, argv);
    client.start();

    APAUSE_MSG("press any key for kill client");
    return 0;
}



