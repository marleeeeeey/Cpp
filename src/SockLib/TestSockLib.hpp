#include "StdPlus/SockLibPlus.hpp"
#include "StdPlus/StdPlus.h"

int main()
{
    AMSG("hello from TestSockLib");
    stdplus::sl_init();
    APAUSE;
    stdplus::sl_term();
    APAUSE;
}