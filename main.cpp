#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("Twootsters");
    a.setOrganizationDomain("github.com/Chronoes/twoots");
    a.setApplicationName("Twoots");
    MainWindow w;
    w.show();

    return a.exec();
}
