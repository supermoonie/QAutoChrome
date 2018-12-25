#include "mainwindow.h"
#include <QApplication>
#include <qautochrome.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QAutoChrome autoChrome;
    MainWindow w;
    w.show();

    return a.exec();
}
