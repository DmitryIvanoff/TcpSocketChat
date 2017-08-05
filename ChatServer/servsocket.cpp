#include "servsocket.h"

ServSocket::ServSocket(QObject *parent) : QObject(parent)
{
    socket=new QTcpSocket(this);
}

ServSocket::~ServSocket()
{
   delete socket;
}

ServSocket::ServSocket(int descriptor)
{
    socket=new QTcpSocket();
    if(!socket->setSocketDescriptor(descriptor))
    {
                emit error(socket->error());
    }
     connect(socket,SIGNAL(connected()),this,SLOT(on_connected()),Qt::DirectConnection);
     connect(socket,SIGNAL(readyRead()),this,SLOT(on_readyRead()),Qt::DirectConnection);
     connect(socket,SIGNAL(disconnected()),this,SLOT(on_disconnected()),Qt::DirectConnection);

}

QByteArray ServSocket::readAll()
{
    return socket->readAll();
}

void ServSocket::close()
{
    socket->close();
}

void ServSocket::writedata(const char *data)
{
    emit readyWrite(data);
}

void ServSocket::on_readyRead()
{
    emit readyRead();
}

void ServSocket::on_connected()
{
    emit connected();
}

void ServSocket::on_disconnected()
{
    socket->deleteLater();
    emit disconnected();
}



void ServSocket::write(const char* data)
{
   socket->write(data);
}

