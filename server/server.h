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
#include "utils.h"
#include "../response_struct.h"

class Server: public QObject
{
Q_OBJECT
public:
    Server(int port, QObject* parent = 0);
    ~Server();

public slots:
    virtual void slotNewConnection();
            void slotReadClient   ();
public:
    std::unique_ptr<QTcpServer> tcp_server;
    quint16 next_block_size;
    void requestManager(QTcpSocket* client, QDataStream& in);
    void sendToClient(QTcpSocket* pSocket, const QString& str);
    void sendTrackToClient(QTcpSocket* client, QDataStream& in);
    void sendPlaylistToClient(QTcpSocket* client, QDataStream& in);
    void sendParsedMusicToClient(QTcpSocket* client, QDataStream& in);
    void sendErrorMsgToClient(QTcpSocket* client, quint8 err_code);
    void sendResultToClient(QTcpSocket* client, ResponseStruct& str);
    void PackToStruct(QDataStream& in);

};

//#include "server_commands.h"
#endif // SERVER_H
