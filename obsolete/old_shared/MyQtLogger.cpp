#include "MyQtLogger.h"

#include <windows.h>    // AllocConsole();

template<class T>
std::ostream & qTypeToOs(std::ostream & os, const T & p)
{
    QString strBuf;
    QDebug dout(&strBuf);
    dout << p;
    os << strBuf.toStdString();
    return os;
}

void qtConsoleOn()
{
    AllocConsole();

    freopen("CONOUT$", "wt", stdout);
    freopen("CONOUT$", "wt", stderr);
}

QDebug & operator<<(QDebug & dout, const std::string & s)
{
    dout << QString::fromStdString(s);
    return dout;
}

std::ostream & operator<<(std::ostream & os, const QPointF & qPoint)
{
    return qTypeToOs(os, qPoint);
}

std::ostream & operator<<(std::ostream & os, const QString & qString)
{
    return qTypeToOs(os, qString);
}

std::ostream & operator<<(std::ostream & os, const QLineF & qLine)
{
    return qTypeToOs(os, qLine);
}
