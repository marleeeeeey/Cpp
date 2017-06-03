#pragma once


#ifdef MY_LOGGER_ON
#   define DEBUG_ENABLE
#endif // MY_LOGGER_ON


#ifdef DEBUG_ENABLE
#   include "MyLoggerEnable.h"
#else
#   include "MyLoggerDisable.h"
#endif // DEBUG_ENABLE
