#include "StdPlus/StdPlus.h"

int main(int argc, char** argv)
{
    AFUN;
    AVAR(argc);

    stdplus::CmdParser cmdParser;
    try
    {
        cmdParser.parseData(argc, argv);
        int lopka = cmdParser.getValue<int>("lopka");
        bool karamba = cmdParser.getValue<bool>("karamba");
        AVAR(lopka);
        AVAR(karamba);
        cmdParser.getValue("kuku");
    }
    catch (const std::exception & exeptionCmdParse)
    {
        AVAR(exeptionCmdParse.what());
    }

    APAUSE_MSG("GoogBye!");
}