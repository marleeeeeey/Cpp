#include <QApplication>
#include "AllInclude.h"
#include "Application.h"

int main(int argc, char *argv[])
{
    qtplus::qtConsoleOn();

    QApplication a(argc, argv);

    Applicaion app;

    return a.exec();
}
