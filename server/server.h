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
#include <utils.h>

class Server: public QWidget
{
Q_OBJECT
public:
    Server(int port, QWidget* parent = 0);
    ~Server();

public slots:
    virtual void slotNewConnection();
            void slotReadClient   ();
private:
    QTcpServer* tcp_server;
    quint16 next_block_size;
    void sendToClient(QTcpSocket* pSocket, const QString& str);
    void sendTrackToClient(QTcpSocket* client, QDataStream& in);
    void sendPlaylistToClient(QTcpSocket* client, QDataStream& in);
    void sendParsedMusicToClient(QTcpSocket* client, QDataStream& in);
    void sendErrorMsgToClient(QTcpSocket* client, quint8 err_code);

};

#endif // SERVER_H
