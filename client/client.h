#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <vector>
#include "utils/delay.h"
#include "response_struct.h"
#include "packmanager.h"
#include "responseparser.h"
#include "baseclient.h"

class Client: public QObject, public BaseClient {
Q_OBJECT

public:

    Client(const std::string& host, int port, QObject* parent = 0);
    ~Client();
    std::string getTrackFromServer(uint8_t& error_code, std::string& track_name); // qstring or music_id
    std::string getParsedTrackFromServer(uint8_t& error_code, std::string& track_name);
    std::vector<std::string> getPlaylistFromServer(uint8_t& error_code);

private slots:
    void slotReadyRead   ();
    void slotError       (QAbstractSocket::SocketError);
    void slotConnected   ();

private:

    std::unique_ptr<QTcpSocket> client;
    quint32 next_block_size;
    quint8 err_code;
    QByteArray tmp_data;
    bool is_executed_response = false;
    void wait_response();
    void sendGetTrack(std::string& track_name);
    void sendGetPlaylist();
    void sendGetParsedTrack(std::string& track_name);

    void responseManager(QDataStream& in) override;
    void sendStructToServer(ResponseStruct&) override;

};


#endif // CLIENT_H
