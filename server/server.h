#ifndef SERVER_H
#define SERVER_H

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
    QThreadPool *pool;
//    void requestManager(qintptr sock_descriptor);
public:

    void sendResultToClient(QTcpSocket* client, ResponseStruct& str);

};


class RequestManagerTask: public QRunnable {

public:
    RequestManagerTask() {}

    void run() {
        std::cout << "Run" << std::endl;
        QDataStream in(client);
        PackManager manag;
        ResponseStruct str =  manag.packToStruct(in);
        server->sendResultToClient(client, str);
    }

    Server* server;
    QTcpSocket* client;

};

//#include "server_commands.h"
#endif // SERVER_H
