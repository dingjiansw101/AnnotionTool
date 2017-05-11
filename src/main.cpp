#include "mainwindow.h"
#include <QApplication>
#include "myview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.show();

    return a.exec();
}
