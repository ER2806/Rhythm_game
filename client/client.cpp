#include "client.h"
#include <string>
#include <algorithm>
#include <functional>
#include <sstream>


Client::Client(const QString& host, int port, QWidget* parent): QWidget(parent), next_block_size(0) {

    this->is_executed_response = false;

    client = new QTcpSocket(this);
    client->connectToHost(host, port);
    connect(client, SIGNAL(connected()), SLOT(slotConnected()));
    connect(client, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(client, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(slotError(QAbstractSocket::SocketError)));

}

Client::~Client(){

    client->close();

}


void Client::slotReadyRead() {

    QDataStream in(client);
    in.setVersion(QDataStream::Qt_5_7);

    if (!client->isOpen())
        std::cout << "client closed" << std::endl;
    for (;;) {

        if (!next_block_size) {
            if (client->bytesAvailable() < static_cast<qint64>(sizeof(quint32))) {
                break;
            }
            in >> next_block_size;
            std::cout << "next_block_size = " << next_block_size << std::endl;
        }

        if (client->bytesAvailable() < next_block_size) {
            break;
        }

        next_block_size = 0;
        responseManager(client, in);

    }

}


void Client::responseManager(QTcpSocket* client, QDataStream& in){

    quint8 comm;
    in >> comm;
    std::cout << "comm = " <<  comm << std::endl;
    switch (comm) {
        case (Commands::ERROR): {
            std::cout << "case 0 " << std::endl;
            QByteArray err_msg;
            in >> err_msg;
            err_code = err_msg.toUInt();
            is_executed_response = true;
            break;

        }

        case (Commands::GET_MUSIC): {
            std::cout << "case 1" << std::endl;
            QByteArray music;
            in >> music;
            QString path = getPathToMusicsFile() + "new.wav";
            QFile file2(path);

             if (!file2.open(QIODevice::WriteOnly))
                 return;

             file2.write(music.data(), music.size());
             file2.close();
             buff = path;
             is_executed_response = true;
             break;
        }

    case (Commands::GET_PLAYLIST): {
            std::cout << "case 2" << std::endl;
            QByteArray playlist;
            in >> playlist;
            std::string res = playlist.toStdString();
            std::replace(res.begin(), res.end(), '\n', ' ');
            std::stringstream ss(res);
            this->playlist.clear();
            std::string tmp;
            while(ss >> tmp){
                std::cout << tmp << std::endl;
                this->playlist.push_back(tmp);
            }
            is_executed_response = true;
            break;
        }
    }

}

void Client::slotError(QAbstractSocket::SocketError err){

    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(client->errorString())
                    );
    std::cerr << strError.toStdString() << std::endl;

}

void Client::slotSendToServer() {

    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    quint8 command = 1;
    out << quint16(0) << quint8(command);
    out << QString("human.mp3");
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    client->write(arrBlock);

}


void Client::slotConnected() {

    std::cout << "Client connected" << std::endl;

}


void Client::sendGetTrack(quint8 command, QString &track_name) {

    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out << quint16(0) << quint8(command);
    out << track_name;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    client->write(arrBlock);

}


QString Client::getTrackFromServer(quint8& error_code, QString& track_name) {

    is_executed_response = false;
    err_code = ErrorCodes::ALL_OK;
    sendGetTrack(quint8(Commands::GET_MUSIC), track_name);

    while(!is_executed_response && err_code == ErrorCodes::ALL_OK){
        delay(3000);
    }
    error_code = err_code;
    return buff;

}


std::vector<std::string> Client::getPlaylistFromServer(quint8& error_code) {

    is_executed_response = false;
    err_code = ErrorCodes::ALL_OK;
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out << quint16(0) << quint8(Commands::GET_PLAYLIST);
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    std::cout << "client -  write get playlist" << std::endl;
    client->write(arrBlock);

    while(!is_executed_response && err_code == ErrorCodes::ALL_OK){
        delay(3000);
    }

    error_code = err_code;
    return playlist;

}
