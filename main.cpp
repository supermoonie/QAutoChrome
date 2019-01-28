#include "mainwindow.h"
#include <QApplication>
#include <qautochrome.h>
#include <page.h>
#include <QDebug>
#include <QAtomicInteger>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    QAutoChrome autoChrome;
//    MainWindow w;
//    w.show();
//    Page page;
    QAtomicInteger<qint64> counter(0);
    qDebug() << counter.fetchAndAddOrdered(1);
    qDebug() << counter.fetchAndAddOrdered(1);
    qDebug() << counter.load();
    QString str;
    qDebug() << str.isNull();
    qDebug() << str.isEmpty();
//    return a.exec();
    return 0;
}
