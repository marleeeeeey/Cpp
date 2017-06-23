
#include "UnzipApplication.h"

int main(int argc, char ** argv)
{
    try
    {
        UnzipApplication app(argc, argv);
    }
    catch (std::logic_error & e)
    {
        AMSG(std::string("APPLICATION ERROR: ") + e.what());
    }

    APAUSE_MSG("Press any key for close programm");
}