#include "mysocket.h"

MySocket::MySocket(QObject *parent): QObject(parent)
{
   data=NULL;
}

void MySocket::start()
{
    socket=new QTcpSocket(this);
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWritten(qint64)));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    socket->connectToHost(QHostAddress::LocalHost,6991); //"10.56.4.212"
    if (!socket->waitForConnected())
    {
       qDebug()<<socket->errorString();
    }
    else
    {
       qDebug()<<" client's connected";
    }

}

void MySocket::close()
{
    if (data!=NULL)
    {
       delete data;
    }
    socket->close();
}

void MySocket::write(const char* data)
{
    socket->write(data);
}

MySocket::~MySocket()
{
}




void MySocket::connected()
{
    qDebug()<<" client's connected";



}

void MySocket::disconnected()
{
    qDebug()<<"client's disconnected";
    socket->deleteLater();
}

void MySocket::readyRead()
{
     data=new QString(socket->readAll());
     emit dataRead(*data);

}

void MySocket::bytesWritten(qint64 bytes)
{
    qDebug()<<"bytes're written: "<<bytes;
}
