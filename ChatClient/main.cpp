#include "mainwindow.h"
#include <QApplication>
#include "dialog.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QIcon icon(":/icons/icon1.png");
     a.setWindowIcon(icon);

    return a.exec();
}
