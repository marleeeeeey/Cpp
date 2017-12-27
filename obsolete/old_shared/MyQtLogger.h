#pragma once

#include "MyQtHelper.h"

#ifdef MY_LOGGER_ON
#   define MY_QTDEBUG_ENABLE
#endif // MY_LOGGER_ON


#ifdef MY_QTDEBUG_ENABLE
#   include "MyQtLoggerEnable.h"
#else
#   include "MyQtLoggerDisable.h"
#endif // MY_QTDEBUG_ENABLE

