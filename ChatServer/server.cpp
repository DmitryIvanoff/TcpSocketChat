#include "server.h"

Server::Server(QObject *parent):QTcpServer(parent)
{
   map=new QMap<QString,Client*>();
   HistoryFile="./history.txt";
}

void Server::StartServer()
{
    if(!this->listen(QHostAddress::Any,6991))
    {
        qDebug()<<"Error: Server is not listening!";
        //error
    }
    else
    {
          qDebug()<<"Listening...";
    }


}

void Server::CloseServer()
{
    QMutableMapIterator<QString,Client*> it(*map);
    while(it.hasNext())
    {
        it.next().value()->close();
    }
    QFile f(HistoryFile);
    if(f.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        f.close();
    }
    close();
}

Server::~Server()
{
    CloseServer();
    delete map;
}

void Server::incomingConnection(int socketDescriptor)
{
     qDebug()<<socketDescriptor<<" connecting";
     client=new Client(this,socketDescriptor);

     connect(client,SIGNAL(dataRead(QByteArray)),this,SLOT(on_dataRead(QByteArray)));  //считали данные от определенного клиента-передали серверу
     connect(client,SIGNAL(nickRead(QByteArray)),this,SLOT(on_nickRead(QByteArray)));
     connect(this,SIGNAL(dataRead(const char*)),client,SLOT(write(const char*)));
     connect(client,SIGNAL(nickDisconnected(QByteArray)),this,SLOT(on_nickDisconnected(QByteArray)));

}

void Server::on_nickRead(const QByteArray &nick)
{
    qDebug()<<"on_nickRead...";
    Client* c=static_cast<Client*>(this->sender());
    map->insert(QString(nick),c);
    QString str(nick);
    str.append(" connected!!!");
    readFromHistory(c);
    writeInHistory(str);
    emit dataRead(str.toStdString().c_str());
}

void Server::on_dataRead(const QByteArray &data)
{
    qDebug()<<"data reading..."<<data;



    writeInHistory(QString(data));
    emit dataRead(data.toStdString().c_str());
}

void Server::on_nickDisconnected(const QByteArray& nick)
{
      qDebug()<<"on_nickDisconnected...";
   map->take(nick);


   QString str(nick);
   str.append(" disconnected..");
  // QMutableMapIterator<QString,Client*> it(*map);
 //  while(it.hasNext())
  // {
  //     it.next().value()->write(str.toStdString().c_str());
  // }
    writeInHistory(str);
    emit dataRead(str.toStdString().c_str());
}

void Server::readFromHistory(Client* c)
{
    QFile f(HistoryFile);
    if(f.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString str;
         QTextStream in(&f);
        while (!f.atEnd())
        {

           str=in.readAll();
           c->write(str.toStdString().c_str());
        }
        f.close();
    }
}

void Server::writeInHistory(const QString &str)
{
    QFile f(HistoryFile);
    if(f.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
    {
        QString s(str);
        s.append("\n");
        QTextStream out(&f);
        out<<s;
        f.close();
    }
}

