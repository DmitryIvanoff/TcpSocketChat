#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QThreadPool>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QByteArray>


class MyThread : public QThread
{
    Q_OBJECT
public:
      MyThread(int descriptor);

protected:
    void run();
signals:
    write(const char*);
    error(QTcpSocket::SocketError err);
    dataRead(const QByteArray&);
    nickRead(const QByteArray&);
    nickDisconnected(const QByteArray&);
public slots:
      void writeData(const char*);
private slots:
    void connected();

    void readyRead();
    void disconnected();
private:
    bool authFlag;
    QByteArray* buffer;
    QTcpSocket* socket;
   // QTcpSocket* socket;
    int socketDescriptor;
    QByteArray ID;

};

#endif // MYTHREAD_H
