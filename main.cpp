#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<a.instance()->thread()->currentThread();
    MainWindow w;
    w.show();
    return a.exec();
}
