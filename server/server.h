#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QWidget>
#include <iostream>
#include <string>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include "../response_struct.h"
#include "baseserver.h"

class Server: public QObject, public BaseServer
{
Q_OBJECT
public:
    Server(int port, QObject* parent = 0);
    ~Server();
    virtual void run() override;

public slots:
    virtual void slotNewConnection();
            void slotReadClient   ();
private:

    std::unique_ptr<QTcpServer> tcp_server;
    quint16 next_block_size;
    void requestManager(QTcpSocket* client);
    void sendResultToClient(QTcpSocket* client, ResponseStruct& str);

};

//#include "server_commands.h"
#endif // SERVER_H
