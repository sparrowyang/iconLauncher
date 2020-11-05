#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //置顶
    Qt::WindowFlags flags = w.windowFlags();
    flags |= Qt::WindowStaysOnTopHint;
    w.setWindowFlags(flags);

    w.show();

    return a.exec();
}
