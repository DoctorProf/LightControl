#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;

    a.setStyle("fusion");
    window.show();
    return a.exec();
}
