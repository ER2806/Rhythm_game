#ifndef MYTHREAD_H
#define MYTHREAD_H


#include <QThread>
#include <QDebug>
#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QVector>
#include <iostream>
#include <string>
#include "../response_struct.h"
#include "baseserver.h"
#include "packmanager.h"

class MyThread : public QThread
{
    Q_OBJECT

public:
    explicit MyThread(qintptr ID, QObject *parent = 0);

    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

private:
    quint16 next_block_size;
    void requestManager();
    void sendResultToClient(ResponseStruct& str);

    QTcpSocket *socket;
    qintptr socketDescriptor;
};

#endif // MYTHREAD_H
