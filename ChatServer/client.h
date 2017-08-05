#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>
#include <QObject>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    Client(QObject *parent, int ID);
signals:
   // write(const char*);
    error(QTcpSocket::SocketError err);
    dataRead(const QByteArray&);
    nickRead(const QByteArray&);
    nickDisconnected(const QByteArray&);
public slots:
    void write(const char*);    //выпоняется, когда клиенту отправляются данные
    void connected();           //выпоняется, когда клиент присоединился
   void close();                //выпоняется, когда клиент хочет отсоединяться
    void readyRead();           //выпоняется, когда есть данные для чтения, считанные данные отправляются к серверу
    void disconnected();        //когда клиент отсоединился
private:
    bool authFlag;
    QByteArray* buffer;
    QTcpSocket* socket;
    int socketDescriptor;       //дескриптор созданного клиентом сокета
    QByteArray ID;
};

#endif // CLIENT_H
