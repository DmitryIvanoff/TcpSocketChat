#ifndef MYRUNNABLE_H
#define MYRUNNABLE_H
#include <QRunnable>
#include <QObject>

class MyRunnable : public QObject,public QRunnable
{
    Q_OBJECT
public:
    MyRunnable(const QByteArray&);
signals:
    finish(const QByteArray&);
private:
    QByteArray data;
protected:
      void run();
};

#endif // MYRUNNABLE_H
