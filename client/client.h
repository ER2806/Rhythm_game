#ifndef CLIENT_H
#define CLIENT_H
#include <QtNetwork>
#include <QWidget>
#include <iostream>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <vector>
#include <QVector>
#include <string>
#include <QString>
#include <utils.h>


class Client: public QWidget {
Q_OBJECT

public:

    Client(const std::string& host, int port, QWidget* parent = 0);
    ~Client();
    std::string getTrackFromServer(uint8_t& error_code, std::string& track_name); // qstring or music_id
    std::string getParsedTrackFromServer(uint8_t& error_code, std::string& track_name);
    std::vector<std::string> getPlaylistFromServer(uint8_t& error_code);

private slots:
    void slotReadyRead   (                            );
    void slotError       (QAbstractSocket::SocketError);
    void slotSendToServer(                            );
    void slotConnected   (                            );
    void closed () {std::cout << "closed" << std::endl;}

private:
    //QTcpSocket* client;
    std::unique_ptr<QTcpSocket> client;
    quint32 next_block_size;
    bool is_error;
    quint8 err_code;
    QString buff;
    bool is_executed_response = false;
    std::vector<std::string> playlist;
    std::vector<quint8> requestes;
    void sendGetTrack(std::string& track_name, quint8 command);
    void sendGetPlaylist();
    void responseManager(std::unique_ptr<QTcpSocket>& client, QDataStream& in);

public:
    void parseResponseGetErrorMsg(QDataStream& in);
    void parseResponseGetMusic(QDataStream& in);
    void parseResponseGetParsedMusic(QDataStream& in);
    void parseResponseGetPlaylist(QDataStream& in);

};

#include "client_commands.h"

#endif // CLIENT_H
