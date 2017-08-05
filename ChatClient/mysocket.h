#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QAbstractSocket>
#include <QByteArray>
#include <QString>
#include <QtNetwork>
class MySocket : public QObject
{
    Q_OBJECT
public:

    explicit MySocket(QObject *parent = 0);
     void start();
     void close();
     void write(const char*);
     ~MySocket();
signals:
    dataRead(const QString&);

 public slots:
    void connected();
    void disconnected();
    void readyRead();
    void bytesWritten(qint64);
private:
    QTcpSocket* socket;
    QString* data;
};

#endif // MYSOCKET_H
