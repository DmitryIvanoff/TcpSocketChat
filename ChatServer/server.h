#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QMap>
# include <QMutableMapIterator>
#include <QFile>
#include "client.h"
class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject* parent = 0);
    void StartServer();
    void CloseServer();
    ~Server();
signals:
    dataRead(const char*);
protected:

    void incomingConnection(int socketDescriptor);
private slots:
    void on_nickRead(const QByteArray&);        //выполняется когда,клиент присоединяется
    void on_dataRead(const QByteArray&);        //выполняется когда,серверу были отправлены данные
    void on_nickDisconnected(const QByteArray&);//выполняется когда,клиент отсоединяется
private:
    void readFromHistory(Client*);
    void writeInHistory(const QString&);
    Client* client;
    QMap<QString,Client*>* map;  //словарь клиентов
    QString HistoryFile;         //файл истории
};

#endif // SERVER_H
