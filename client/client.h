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
    bool is_executed_response = false;

    Client(const QString& host, int port, QWidget* parent = 0);
    ~Client();
    QString getTrackFromServer(quint8& error_code, QString& track_name); // qstring or music_id
    std::vector<std::string> getPlaylistFromServer(quint8& error_code);
    void sendGetTrack(quint8 command, QString& track_name);


private slots:
    void slotReadyRead   (                            );
    void slotError       (QAbstractSocket::SocketError);
    void slotSendToServer(                            );
    void slotConnected   (                            );
    void closed () {std::cout << "closed" << std::endl;}

private:
    QTcpSocket* client;
    quint32 next_block_size;
    bool is_error;
    quint8 err_code;
    QString buff;
    std::vector<std::string> playlist;
    std::vector<quint8> requestes;
    void responseManager(QTcpSocket* client, QDataStream& in);

};

#endif // CLIENT_H
