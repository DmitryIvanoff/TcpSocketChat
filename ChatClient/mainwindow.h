#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QDebug>
#include "mysocket.h"
#include "dialog.h"
#include <QShortcut>
#include <QVBoxLayout>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *);
private slots:
    void on_commandLinkButton_clicked();
    void on_dataRead(const QString&);
    void on_nickRead(const QString&);
private:
    QShortcut* sh;
    Dialog* dialog;
    MySocket* socket;
    Ui::MainWindow *ui;
    QString nick;


};

#endif // MAINWINDOW_H
