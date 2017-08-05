#include "client.h"

Client::Client(QObject *parent, int ID) : QObject(parent)
{
    socketDescriptor=ID;
    authFlag=false;
    buffer=NULL;
    socket=new QTcpSocket(this);
    if (!socket->setSocketDescriptor(ID))
    {
        emit error(socket->error());
    }
    connect(socket,SIGNAL(connected()),this,SLOT(connected()),Qt::DirectConnection);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);
}

void Client::write(const char *data)
{
    socket->write(data);
}

void Client::connected()
{

}

void Client::close()
{
    socket->close();
}

void Client::readyRead()
{
    if (!authFlag)
     {
       ID=socket->readAll();
       emit nickRead(ID);
       authFlag=true;
     }
     else
     {
         QByteArray data=socket->readAll();
         emit dataRead(data);
     }
}

void Client::disconnected()
{
    emit nickDisconnected(ID);
}

