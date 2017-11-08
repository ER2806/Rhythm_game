#include "client.h"
#include <string>
#include <algorithm>
#include <functional>
#include <sstream>


Client::Client(const std::string& host, int port, QWidget* parent): QWidget(parent), next_block_size(0) {

    this->is_executed_response = false;

    client = new QTcpSocket(this);
    client->connectToHost(QString::fromStdString(host), port);
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
//            std::cout << "next_block_size = " << next_block_size << std::endl;
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
    switch (comm) {
        case (Commands::ERROR): {
            //std::cout << "case 0 " << std::endl;
            in >> err_code;
            is_executed_response = true;
            break;

        }

        case (Commands::GET_MUSIC): {
            //std::cout << "case 1" << std::endl;
            QByteArray music;
            in >> music;
            QString path = getPathToMusicsFile() + "new.wav";
            QFile file2(path);

             if (!file2.open(QIODevice::WriteOnly)){
                 err_code = ErrorCodes::FILE_NOT_CREAT;
                 return;
             }

             file2.write(music.data(), music.size());
             file2.close();
             buff = path;
             is_executed_response = true;
             break;
        }

        case (Commands::GET_PLAYLIST): {
            //std::cout << "case 2" << std::endl;
            QByteArray playlist;
            in >> playlist;
            std::string res = playlist.toStdString();
            std::replace(res.begin(), res.end(), '\n', ' ');
            std::stringstream ss(res);
            this->playlist.clear();
            std::string tmp;
            while(ss >> tmp){
                //std::cout << tmp << std::endl;
                this->playlist.push_back(tmp);
            }
            is_executed_response = true;
            break;
        }

        case (Commands::GET_PARSED_MUSIC): {
            //std::cout << "case 3" << std::endl;
            QByteArray parsed_music;
            in >> parsed_music;
            QString path = getPathToParsedMusicsFile() + "parsed";
            //std::cout << path.toStdString() << std::endl;
            QFile file(path);
            if (!file.open(QIODevice::WriteOnly)) {
                err_code = ErrorCodes::FILE_NOT_CREAT;
                return;
            }
            file.write(parsed_music);
            file.close();
            buff = path;
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


std::string Client::getTrackFromServer(uint8_t& error_code, std::string& track_name) {

    is_executed_response = false;
    err_code = ErrorCodes::ALL_OK;
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out << quint16(0) << quint8(Commands::GET_MUSIC);
    out << QString::fromStdString(track_name);
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    client->write(arrBlock);

//    sendGetTrack(quint8(Commands::GET_MUSIC), track_name);

    while(!is_executed_response && err_code == ErrorCodes::ALL_OK){
        delay(100);
    }

    error_code = err_code;
    return buff.toStdString();

}

std::string Client::getParsedTrackFromServer(uint8_t& error_code, std::string& track_name) {

    is_executed_response = false;
    err_code = ErrorCodes::ALL_OK;
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out << quint16(0) << quint8(Commands::GET_PARSED_MUSIC);
    out << QString::fromStdString(track_name);
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    client->write(arrBlock);

    while(!is_executed_response && err_code == ErrorCodes::ALL_OK){
        delay(100);
    }
    error_code = err_code;

    return buff.toStdString();

}

std::vector<std::string> Client::getPlaylistFromServer(uint8_t& error_code) {

    is_executed_response = false;
    err_code = ErrorCodes::ALL_OK;
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out << quint16(0) << quint8(Commands::GET_PLAYLIST);
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    //std::cout << "client -  write get playlist" << std::endl;
    client->write(arrBlock);

    while(!is_executed_response && err_code == ErrorCodes::ALL_OK){
        delay(100);
    }

    error_code = err_code;
    return playlist;

}