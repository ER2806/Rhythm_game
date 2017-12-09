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
#include "utils/enumcommands.h"
#include "utils/networkutils.h"
#include "utils/delay.h"
#include "../response_struct.h"
#include "packmanager.h"
#include "responseparser.h"

class Client: public QWidget {
Q_OBJECT

public:

    Client(const std::string& host, int port, QWidget* parent = 0);
    ~Client();
    std::string getTrackFromServer(uint8_t& error_code, std::string& track_name); // qstring or music_id
    std::string getParsedTrackFromServer(uint8_t& error_code, std::string& track_name);
    std::vector<std::string> getPlaylistFromServer(uint8_t& error_code);

private slots:
    void slotReadyRead   ();
    void slotError       (QAbstractSocket::SocketError);
    void slotConnected   ();
    void closed () {std::cout << "closed" << std::endl;}

private:

    std::unique_ptr<QTcpSocket> client;
    quint32 next_block_size;
    quint8 err_code;
    QByteArray tmp_data;
    bool is_executed_response = false;

    void sendGetTrack(std::string& track_name, quint8 command);
    void sendGetPlaylist();
    void sendGetParsedTrack(std::string& track_name);
    void responseManager(std::unique_ptr<QTcpSocket>& client, QDataStream& in);
    void sendStructToServer(ResponseStruct&);

};


#endif // CLIENT_H
