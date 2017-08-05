#ifndef SERVSOCKET_H
#define SERVSOCKET_H
#include <QTcpSocket>
#include <QObject>

class ServSocket : public QObject
{
    Q_OBJECT
public:
    explicit ServSocket(QObject *parent = 0);
    ~ServSocket();
    ServSocket(int descriptor);
    QByteArray readAll();
signals:
     error(QTcpSocket::SocketError err);
    readyWrite(const char*);
    readyRead();
    connected();
    disconnected();
public slots:
    void close();
    void writedata(const char*data);
    void write(const char*);
    void on_readyRead();
    void on_connected();
    void on_disconnected();

private:
 QTcpSocket* socket;
};

#endif // SERVSOCKET_H
