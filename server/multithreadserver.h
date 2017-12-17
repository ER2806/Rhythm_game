#ifndef MULTITHREADSERVER_H
#define MULTITHREADSERVER_H

#include <QTcpServer>
#include "baseserver.h"
#include <QObject>

class MultithreadServer: public QTcpServer, public BaseServer
{
    Q_OBJECT
public:
    explicit MultithreadServer(int port, QObject* parent = 0);
    virtual void run() override;

protected:
    void incomingConnection( qintptr socketDescriptor );

};

#endif // MULTITHREADSERVER_H
