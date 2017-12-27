#pragma once

#define QTDEBUG_API inline

#include <QDebug>

QTDEBUG_API void qtConsoleOn() {}

QTDEBUG_API std::ostream & operator<<(std::ostream & os, const QPointF & qObj) { return os; }
QTDEBUG_API std::ostream & operator<<(std::ostream & os, const QLineF & qObj) { return os; }
QTDEBUG_API std::ostream & operator<<(std::ostream & os, const QString & qstring) { return os; }
