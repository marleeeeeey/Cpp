#pragma once


#ifndef QTDEBUG_EXPORT
#    pragma comment(lib, "MyQtLogger.lib")
#    define QTDEBUG_API __declspec(dllimport)
#else 
#    define QTDEBUG_API __declspec(dllexport)
#endif 

#include <QDebug>

QTDEBUG_API void qtConsoleOn();

QTDEBUG_API std::ostream & operator<<(std::ostream & os, const QPointF & qObj);
QTDEBUG_API std::ostream & operator<<(std::ostream & os, const QLineF & qObj);
QTDEBUG_API std::ostream & operator<<(std::ostream & os, const QString & qstring);
