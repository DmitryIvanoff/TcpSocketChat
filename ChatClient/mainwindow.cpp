#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dialog=new Dialog(this);
    connect(dialog,SIGNAL(nickRead(QString)),this,SLOT(on_nickRead(QString)));
    dialog->show();
    socket=new MySocket(this);

    connect(socket,SIGNAL(dataRead(QString)),this,SLOT(on_dataRead(QString)));

    sh=new QShortcut(ui->textEdit);
    sh->setKey(Qt::CTRL+Qt::Key_Return);
    connect(sh,SIGNAL(activated()),this,SLOT(on_commandLinkButton_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
    //delete sh;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->gridLayoutWidget->resize(event->size().width()-40,event->size().height()-40);
    QMainWindow::resizeEvent(event);
}

void MainWindow::on_commandLinkButton_clicked()
{
    if (!(ui->textEdit->toPlainText()==QString("")))
    {
      QString s=nick;
      s.append(": ");
      s.append(ui->textEdit->toPlainText());
      socket->write(s.toStdString().c_str());
      ui->textEdit->clear();
    }

}

void MainWindow::on_dataRead(const QString &text)
{
    ui->textBrowser->append(text);
}

void MainWindow::on_nickRead(const QString &s)
{
    nick=s;
    ui->gridLayout->setRowStretch(0,15);
    ui->gridLayout->setRowStretch(1,5);
    dialog->close();
    this->show();
    socket->start();
    socket->write(nick.toStdString().c_str());
}
