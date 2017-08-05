#include "mainwindow.h"
#include <QApplication>
#include "server.h"
#include <QRunnable>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QIcon icon(":/icons/icon1.png");
    a.setWindowIcon(icon);
    w.show();
    Server serv;
    serv.StartServer();
    return a.exec();
}
