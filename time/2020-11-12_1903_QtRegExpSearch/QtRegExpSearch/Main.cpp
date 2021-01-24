#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("MarleeeeeeySoft");
    a.setOrganizationDomain("marleeeeeey.com");
    a.setApplicationName("SuperFinder");
    MainWindow w;
    w.show();
    return a.exec();
}
