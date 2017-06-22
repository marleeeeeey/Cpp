

#include "StdPlus/StdPlus.h"


int main(int argc, char ** argv)
{
    AMSG("Hello from UnzipManager");

    stdplus::SimpleCmdParser cmd;
    cmd.parseData(argc, argv);

    std::string fileName = cmd.indexedValues().at(1);

    stdplus::SimpleSettingsPlus settings;
    settings.open(fileName);


    APAUSE;
}