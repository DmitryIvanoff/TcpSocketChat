#include "mythread.h"



MyThread::MyThread(int descriptor)
{
    socketDescriptor=descriptor;
    authFlag=false;
    buffer=NULL;


}


void MyThread::run()
{
    socket=new QTcpSocket();
    if (!socket->setSocketDescriptor(socketDescriptor))
    {
        emit error(socket->error());
    }

    connect(socket,SIGNAL(connected()),this,SLOT(connected()),Qt::DirectConnection);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);


    qDebug()<<socketDescriptor<<"was opened";
    exec();
}



void MyThread::connected()
{

}



void MyThread::writeData(const char* data)
{
    buffer=new QByteArray(data);

}

void MyThread::readyRead()
{
      //read()




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



   msleep(200);
   //time consumer
   if (buffer!=NULL)
   {

       qDebug()<<"Server's writing "<< socketDescriptor;
       socket->write(*buffer);
    delete buffer;


   }



}

void MyThread::disconnected()
{

    emit nickDisconnected(ID);
    socket->deleteLater();
    exit(0);

}
